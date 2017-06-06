#ifndef TANK_H
#define TANK_H
#include"Point.h"//�����а���cmath��
#include<ctime>
class Tank {
protected:
	double m_hp;
	double m_damage;
	double m_AtaDistance;//attack distance
	Point m_pos;//position
public:
	Tank();
	Tank(const Point&);//�������괴����λ
	Tank(const double& hp, const double&, const double&, const Point&);
	~Tank() {};
	const double& getAtaDistance()const;
	const double& getHp()const;
	void setpos(const Point&);
	void setpos(const int& x, const int& y);
	double distance(const Tank&);//������Tank����
	Point& rePos();
	void atack(Tank&);//ĳ��λ������һ��λ
};
#endif