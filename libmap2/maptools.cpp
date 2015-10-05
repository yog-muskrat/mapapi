#include "maptools.h"

#include <qmath.h>

double MapTools::radToDegree(const double &rad)
{
	return rad * 180. / M_PI;
}

double MapTools::degreeToRad(const double &degree)
{
	return degree * M_PI / 180.;
}

Coord MapTools::planeToGeo(HMAP mapHnd, const CoordPlane &coordPlane)
{
	double lat = coordPlane.x;
	double lng = coordPlane.y;

	mapPlaneToGeo(mapHnd, &lat, &lng);

	lat = radToDegree(lat);
	lng = radToDegree(lng);

	return Coord(lat, lng);
}

CoordPlane MapTools::geoToPlane(HMAP mapHnd, const Coord &coord)
{
	double x = degreeToRad( coord.lat );
	double y = degreeToRad( coord.lng );

	mapGeoToPlane(mapHnd, &x, &y);

	return CoordPlane(x, y);
}

QPoint MapTools::planeToPicture(HMAP mapHnd, const CoordPlane &coord)
{
	double x = coord.x;
	double y = coord.y;

	mapPlaneToPicture(mapHnd, &x, &y);

	return QPoint(x, y);
}

QPoint MapTools::geoToPicture(HMAP mapHnd, const Coord &coord)
{
	CoordPlane coordPlane = geoToPlane(mapHnd, coord);

	return planeToPicture( mapHnd, coordPlane );
}