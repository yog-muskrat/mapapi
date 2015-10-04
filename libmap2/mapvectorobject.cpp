#include "mapvectorobject.h"
#include "maplayer.h"
#include "maptools.h"

#include "qmath.h"
#include <QDebug>
#include <qline.h>

MapVectorObject::MapVectorObject(long rscCode, MapLayer *layer)
	: MapObject(MO_Vector, layer), mRotation(0), mCoord( CoordPlane() )
{
	mapRegisterObject(mObjHandle, rscCode, LOCAL_VECTOR);
	mapAppendPointPlane(mObjHandle, 0, 0);
	mapAppendPointPlane(mObjHandle, 0, 0);
	setRotation(0);

	commit();
}

void MapVectorObject::setCoordinates(Coord coord)
{
	if(mObjHandle <= 0)
	{
		return;
	}

	setCoordinates(coord.toPlane( mapLayer()->mapHandle() ));
}

void MapVectorObject::setCoordinates(CoordPlane coord)
{
	if(mCoord == coord)
	{
		return;
	}

	mCoord = coord;

	updateMetric(1, mCoord);
	setRotation( rotation() );
	commit();

//	pLayer->objectChangedNotify(this);
}

Coord MapVectorObject::coordinatesGeo()
{
	return mCoord.toGeo( mapLayer()->mapHandle() );
}

CoordPlane MapVectorObject::coordinatesPlane()
{
	return mCoord;
}

double MapVectorObject::planeX()
{
	return mCoord.x;
}

double MapVectorObject::planeY()
{
	return mCoord.y;
}

double MapVectorObject::lat()
{
	return mCoord.toGeo( mapLayer()->mapHandle() ).lat;
}

double MapVectorObject::lng()
{
	return mCoord.toGeo( mapLayer()->mapHandle() ).lng;
}

void MapVectorObject::setRotation(double degree)
{
//	if(degree == mRotation)
//	{
//		return;
//	}

	mRotation = degree;

	QLineF line( mCoord.toPointF(), mCoord.toPointF() + QPointF(1000, 0));
	line.setAngle(mRotation - 90);

	updateMetric(2, CoordPlane( line.p2()) );
	commit();

//	pLayer->objectChangedNotify(this);
}
