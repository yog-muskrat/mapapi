#ifndef STRUCTS
#define STRUCTS

#include <QPoint>
#include <QVariant>

#ifndef MAPTYPE_H
typedef long int HMAP;
typedef long int HOBJ;
typedef long int HRSC;
typedef long int HSITE;
typedef long int HSELECT;
#endif

namespace Map2
{

struct CoordPlane;

/*!
 * \brief Координата в формате "градусы + десятая часть"
 */
struct Coord
{
	double lat;
	double lng;

	Coord() : lat(0), lng(0) {}
	Coord(double lat, double lng) : lat(lat), lng(lng) {}
	Coord(const Map2::Coord &other) : lat(other.lat), lng(other.lng) {}

	QString toString() const { return QString("Ш:%0 Д:%1").arg(lat, 0, 'f').arg(lng, 0, 'f'); }
	bool operator ==(const Map2::Coord &other) const { return other.lat == lat && other.lng == lng;}

	/*!
	 * \brief Пересчитывает координаты из градусов с минутами.
	 */
	static Coord fromDegreeWithMinutes(const double &lat, const double &lng);
};

/*!
 * \brief Координаты в метрах на местности.
 */
struct CoordPlane
{
	double x;
	double y;

	CoordPlane() : x(0), y(0) {}
	CoordPlane(double x, double y) : x(x), y(y) {}
	CoordPlane(const Map2::CoordPlane &other) : x(other.x), y(other.y) {}
	explicit CoordPlane( const QPointF &point) : x(point.y()), y( point.x()) {}

	QPointF toPointF(){ return QPointF(x, y); }

	QString toString() const { return QString("X:%0 Y:%1").arg(x, 0, 'f').arg(y, 0, 'f'); }
	bool operator ==(const Map2::CoordPlane &other) const { return other.x == x && other.y == y;}

	CoordPlane operator+(const Map2::CoordPlane &right);
	CoordPlane& operator+=(const Map2::CoordPlane &other);

	CoordPlane operator-(const Map2::CoordPlane &right);
	CoordPlane& operator-=(const Map2::CoordPlane &other);
};

}
Q_DECLARE_METATYPE(Map2::Coord)
Q_DECLARE_METATYPE(Map2::CoordPlane)

#endif // STRUCTS
