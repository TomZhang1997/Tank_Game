#include"Point.h"
Point::Point():m_x(0),m_y(0){}
Point::Point(const int& x, const int& y) : m_x(x), m_y(y) {};
void Point::set(const int& x, const int& y) {
	m_x = x;
	m_y = y;
	return;
}
double Point::distance(const Point& po) {
	return sqrt((m_x - po.m_x)*(m_x - po.m_x) + (m_y - po.m_y)*(m_y - po.m_y));
}
const int Point::getX()const { return m_x; }
const int Point::getY()const { return m_y; }
