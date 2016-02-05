#include "actions/mapvectorobjectaction.h"

#include "maplayer.h"
#include "maphelper.h"
#include "rscviewer.h"
#include "mapcanvas.h"
#include "objects/mapvectorobject.h"

#include <QMessageBox>

using namespace Map2;

MapVectorObjectAction::MapVectorObjectAction(Map2::MapView *view) : MapAction(view)
{

}

bool MapVectorObjectAction::processMouseDblClickEvent(QMouseEvent *mouseEvent)
{
	if(!pView->activeLayer())
	{
		QMessageBox::information(pView, "Добавление объекта", "Не задан активный слой карты.", "Закрыть");
		return true;
	}

	int exCode = RscViewer::selectVectorExCode(pView->activeLayer()->rscName());

	if(exCode <= 0)
	{
		return true;
	}

	MapVectorObject *obj = new MapVectorObject(exCode, pView->activeLayer());

	QPoint pictureCoord = pView->canvas()->mapTopLeft() + mouseEvent->pos();
	obj->setCoordinates( pView->helper()->pictureToPlane(pictureCoord) );

	return false;
}
