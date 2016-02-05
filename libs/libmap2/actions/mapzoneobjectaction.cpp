#include "actions/mapzoneobjectaction.h"

#include "maplayer.h"
#include "maphelper.h"
#include "mapcanvas.h"
#include "rscviewer.h"
#include "objects/mapzoneobject.h"

#include <QMessageBox>
#include <QDebug>

using namespace Map2;

MapZoneObjectAction::MapZoneObjectAction(Map2::MapView *view)
	: MapAction(view), pObject(0)
{

}

MapZoneObjectAction::~MapZoneObjectAction()
{
	if(pObject)
	{
		pObject->remove();
	}
}

bool MapZoneObjectAction::processMouseClickEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		CoordPlane coord = pView->helper()->pictureToPlane( pView->canvas()->mapTopLeft() + mouseEvent->pos() );
		if(!pObject)
		{
			if(!pView->activeLayer())
			{
				QMessageBox::information(pView, "Добавление зоны", "Не задан активный слой карты.", "Закрыть");
				return true;
			}

			int exCode = RscViewer::selectZoneExCode(pView->activeLayer()->rscName());
			if(exCode <= 0)
			{
				return false;
			}

			QList<CoordPlane> coords;
			coords << coord;

			pObject =  pView->activeLayer()->addZoneObject(exCode, coords);
		}
		else
		{
			pObject->addPoint(coord);
			return false;
		}
	}

	return true;
}

bool MapZoneObjectAction::processMouseDblClickEvent(QMouseEvent *mouseEvent)
{
	if(mouseEvent->button() == Qt::LeftButton)
	{
		CoordPlane coord = pView->helper()->pictureToPlane( pView->canvas()->mapTopLeft() + mouseEvent->pos() );

		if(pObject)
		{
			pObject->addPoint(coord);
			pObject->closeZone();
			pObject = 0;
			return false;
		}
	}

	return true;
}

void MapZoneObjectAction::setEnabled(const bool enabled)
{
	if(!enabled && pObject)
	{
		pObject->remove();
		pObject = 0;
	}
}
