#ifndef MAPCOMMLINEOBJECT_H
#define MAPCOMMLINEOBJECT_H

#include "map2/objects/mapobject.h"

#include <QColor>
#include <QPolygonF>

namespace Map2
{
class MapCommlineObject : public MapObject
{
public:
	enum ArrowStyle
	{
		AS_NoArrows,
		AS_StartArrow,
		AS_EndArrow,
		AS_BothArrows
	};

	MapCommlineObject(const Map2::Coord &from, const Map2::Coord &to, Map2::MapLayer * layer = 0);

	~MapCommlineObject();

	QColor color() const { return mColor; }
	void setColor(const QColor &color);

	Map2::Coord from() const { return mFrom; }
	void setFrom(const Map2::Coord &from);

	Map2::Coord to() const { return mTo; }
	void setTo(const Map2::Coord &to);

	Map2::MapCommlineObject::ArrowStyle arrowStyle() const { return mArrowStyle; }
	void setArrowStyle(const Map2::MapCommlineObject::ArrowStyle &arrowStyle);

	double lineWidth() const { return mLineWidth; }
	void setLineWidth(double value);

private:
	QPolygonF drawArcs();
	QPolygonF drawArc(QPointF from, QPointF to, qreal radius);

	HMAP addArrow(CoordPlane pointCoord, double azimuth) const;

	Coord mFrom;
	Coord mTo;
	QColor mColor;
	ArrowStyle mArrowStyle;
	double mLineWidth;

	HOBJ hBody;
	HOBJ hToHandle;
	HOBJ hFromHandle;

	// MapObject interface
public:
	virtual Coord coordinateGeo() const { return mFrom; }
	virtual void moveBy(double dxPlane, double dyPlane);
	virtual QList<HOBJ*> mapHandles();

protected:
	virtual void repaint();

};
}

#endif // MAPCOMMLINEOBJECT_H
