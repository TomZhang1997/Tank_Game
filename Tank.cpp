#include"Tank.h"
Tank::Tank():m_pos(-1,-1),m_hp(10),m_damage(1),m_AtaDistance(2){}
Tank::Tank(const Point& pos) :m_pos(pos),m_hp(10), m_damage(1), m_AtaDistance(2) {};
Tank::Tank(const double& hp, const double& dama, const double& dis, const Point& pos) :m_pos(pos),m_hp(hp), m_damage(dama), m_AtaDistance(dis) {};
void Tank::setpos(const Point& pos){
	m_pos = pos;
	return;
}
void Tank::setpos(const int& x, const int& y) {
	m_pos = Point(x, y);
	return;
}
const double& Tank::getAtaDistance()const { return m_AtaDistance; }

const double& Tank::getHp()const { return m_hp; }

double Tank::distance(const Tank& ta) {
	return m_pos.distance(ta.m_pos);
}

Point& Tank::rePos() {
	return m_pos;
}
void Tank::atack(Tank&ta) {
	srand(time(0));
	//������ʧ���ʣ�����Խ��Խ�����׶�ʧ
	double miss = (rand() % 101)/100 - (1 - m_pos.distance(ta.m_pos) / m_AtaDistance);
	//0.4����Զ�������и���
	if (miss > 0.4)return;
	//���к�����˺��̶�
	ta.m_hp -= m_damage;
	return;
}

