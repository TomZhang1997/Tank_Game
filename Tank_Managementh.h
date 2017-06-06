#ifndef TANK_MANAGEMENT_H
#define TANK_MANAGEMENT_H
#include"Tank.h"
#include<vector>
using namespace std;
class Tank_Management {
private:
	vector<Tank> m_red;
	vector<Tank> m_black;
	double m_fitness;//����population������
	double m_normalFitness;//��׼��֮���fitness������population
	double m_weight;//Ȩ��
public:
	Tank_Management();
	Tank_Management(const vector<Tank>& red, const vector<Tank>& black);
	void updateFitness();//����˫�����ͣ���ɫ���Ʒ�����������ɫ���Ʒ��ظ�������ֵ�������ƴ�С
	vector<Tank>& reRed();
	vector<Tank>& reBlack();
	double& reFitness();
	double& reNorFit();
	double& reWeight();
	bool ifOverlap(const int&, const int&);//�鿴x,y��Ӧ�ĵ��Ƿ����غ�,�غϷ���1�����غϷ���0
	bool ifOverlap(const Point&);
};

#endif