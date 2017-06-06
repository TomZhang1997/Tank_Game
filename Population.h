#ifndef POPULATION_H
#define POPULATION_H
#include"Tank_Managementh.h"
#include<cmath>
class Population {
private:
	vector<Tank_Management> m_population;//���������͹��ɵ���Ⱥ����
	vector<vector<double>> m_PM;//���ʾ���probability matrix
	Tank_Management m_backup;//���캯����backup�����������managementһ��
public:
	Population(const Tank_Management&);//���캯�����������Ⱥ�������Ͷ���һ���ģ���
	Tank_Management& reBackup();
	vector<Tank_Management>& rePopulation();
	const int getPopSize();
	void updatePopFitness();//������Ⱥ����Tank_Management��fitness
	void updatePopWeight();//����weight,����m_population
	void updatePM();//���¸��ʾ���PM��PMֱ����m_population������m_populaiton�����м�¼���Ž�Ĺ���
	void setPopRan();//�ڷ��̶�����£�����Ⱥ���еĺ췽��λ������ڵ�ͼ�� set population randomly
	void setPopUni();//�԰���ͨ��ʽ���������Ⱥ������
	const Point getPMPoint();
	const double getAverageFit();//��ȡ��Ⱥƽ����ӦֵFitness
	void showPM();
};
#endif