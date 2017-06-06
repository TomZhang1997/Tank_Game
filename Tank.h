#ifndef TANK_H
#define TANK_H
#include"Point.h"//点类中包含cmath类
#include<ctime>
class Tank {
protected:
	double m_hp;
	double m_damage;
	double m_AtaDistance;//attack distance
	Point m_pos;//position
public:
	Tank();
	Tank(const Point&);//给定坐标创建单位
	Tank(const double& hp, const double&, const double&, const Point&);
	~Tank() {};
	const double& getAtaDistance()const;
	const double& getHp()const;
	void setpos(const Point&);
	void setpos(const int& x, const int& y);
	double distance(const Tank&);//计算两Tank距离
	Point& rePos();
	void atack(Tank&);//某单位攻击另一单位
};
#endif