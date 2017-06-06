#ifndef TANK_MANAGEMENT_H
#define TANK_MANAGEMENT_H
#include"Tank.h"
#include<vector>
using namespace std;
class Tank_Management {
private:
	vector<Tank> m_red;
	vector<Tank> m_black;
	double m_fitness;//用于population的评估
	double m_normalFitness;//标准化之后的fitness，用于population
	double m_weight;//权重
public:
	Tank_Management();
	Tank_Management(const vector<Tank>& red, const vector<Tank>& black);
	void updateFitness();//评估双方阵型，红色优势返回正数，黑色优势返回负数，数值代表优势大小
	vector<Tank>& reRed();
	vector<Tank>& reBlack();
	double& reFitness();
	double& reNorFit();
	double& reWeight();
	bool ifOverlap(const int&, const int&);//查看x,y对应的点是否有重合,重合返回1，不重合返回0
	bool ifOverlap(const Point&);
};

#endif