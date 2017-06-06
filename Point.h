#ifndef POINT_H
#define POINT_H
#include<cmath>
#include<iostream>
class Point {
protected:
	int m_x;
	int m_y;
public:
	~Point() {};
	Point();
	Point(const int&, const int&);
	const int getX()const;
	const int getY()const;
	void set(const int& x, const int& y);
	double distance(const Point&);
};
#endif
