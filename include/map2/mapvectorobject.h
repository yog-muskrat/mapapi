#ifndef MAPVECTOROBJECT_H
#define MAPVECTOROBJECT_H

#include "mapobject.h"
#include "structs.h"

#include "gis/mapapi.h"
#include "gis/maptype.h"

#include <QString>

class MapVectorObject : public MapObject
{
public:
	MapVectorObject(long rscCode, MapLayer * layer = 0);

	void setCoordinates(Coord coord);
	void setCoordinates(CoordPlane coord);
	Coord coordinatesGeo();
	CoordPlane coordinatesPlane();
	double planeX();
	double planeY();
	double lat();
	double lng();

	double rotation() const;
	void setRotation(double degree);
};

#endif // MAPVECTOROBJECT_H