#include "mapobject.h"
#include "maplayer.h"
#include "mapview.h"

MapObject::MapObject(Type t, MapLayer *layer): mType(t), mObjHandle(-1), pLayer(layer)
{
	mObjHandle = mapCreateSiteObject(mapLayer()->mapHandle(), mapLayer()->siteHandle(), 1, IDFLOAT2 );

	layer->addObject(this);
}

MapObject::~MapObject()
{
	Q_ASSERT(handle() > 0);

	mapCommitObject(handle());
	mapFreeObject(handle());
}

void MapObject::remove()
{
	Q_ASSERT(handle() > 0);

	mapDeleteObject( handle() );
	mapCommitObject( handle() );
	mapFreeObject( handle() );

	mObjHandle = 0;
}

void MapObject::center()
{
	Q_ASSERT(handle() > 0 && mapLayer() );

	mapLayer()->mapView()->setCenter( coordinate() );
}

void MapObject::setSelected(bool b)
{

}

CoordPlane MapObject::coordinate() const {
	double x = mapXPlane( handle() );
	double y = mapYPlane( handle() );

	return CoordPlane(x, y);
}

QString MapObject::typeName() const
{
	if(mType == MO_Vector)
	{
		return "Одиночный";
	}
	else if(mType == MO_Line)
	{
		return "Линия";
	}
	else if(mType == MO_Zone)
	{
		return "Зона";
	}

	return "";
}

void MapObject::setMapLayer(MapLayer *layer)
{
	if(layer == pLayer)
	{
		return;
	}

	pLayer = layer;
	pLayer->addObject( this );
	mapChangeObjectMap(handle(), layer->mapHandle(), layer->siteHandle());
	mapCommitObject(handle());
}

void MapObject::commit()
{
	mapCommitObject(handle());
}

void MapObject::addMetricBinding(MetricBinding binding, int targetMetric)
{
	if(mObjectsBindings.contains(targetMetric, binding))
	{
		return;
	}

	mObjectsBindings.insertMulti(targetMetric, binding);
}

void MapObject::removeMetricBinding(MetricBinding binding, int targetMetric)
{
	mObjectsBindings.remove(targetMetric, binding);
}

void MapObject::setName(QString name)
{
	mName = name;

	pLayer->objectChangedNotify(this);
}

void MapObject::bindMetric(int metricNumber, MapObject *targetObject, int targetMetricNumber)
{
	unbindMetric(metricNumber);

	MetricBinding mb;
	mb.object = targetObject;
	mb.metricNumber = targetMetricNumber;

	targetObject->addMetricBinding(MetricBinding(this, metricNumber), targetMetricNumber);
	mMetricsBindings[metricNumber] = mb;
}

void MapObject::unbindMetric(int metricNumber)
{
	if(mMetricsBindings.contains(metricNumber))
	{
		MetricBinding mb = mMetricsBindings.take( metricNumber );
		mb.object->removeMetricBinding( MetricBinding(this, metricNumber), mb.metricNumber);
	}
}

void MapObject::unbindMetrics()
{
	foreach(int i, mMetricsBindings.keys())
	{
		MetricBinding &mb = mMetricsBindings[i];
		mb.object->removeMetricBinding( MetricBinding(this, i), mb.metricNumber);
	}

	mMetricsBindings.clear();
}

void MapObject::updateMetric(int metricNumber, CoordPlane coord)
{
	mapUpdatePointPlane(handle(), coord.x, coord.y, metricNumber);

	foreach(const MetricBinding &mb, mObjectsBindings.values(metricNumber))
	{
		mb.object->updateMetric(mb.metricNumber, coord);
		mb.object->commit();
	}
}
