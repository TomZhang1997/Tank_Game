#ifndef POPULATION_H
#define POPULATION_H
#include"Tank_Managementh.h"
#include<cmath>
class Population {
private:
	vector<Tank_Management> m_population;//多个红黑阵型构成的种群容器
	vector<vector<double>> m_PM;//概率矩阵probability matrix
	Tank_Management m_backup;//构造函数中backup和用来构造的management一样
public:
	Population(const Tank_Management&);//构造函数所构造的种群所有阵型都是一样的！！
	Tank_Management& reBackup();
	vector<Tank_Management>& rePopulation();
	const int getPopSize();
	void updatePopFitness();//更新种群所有Tank_Management的fitness
	void updatePopWeight();//更新weight,根据m_population
	void updatePM();//更新概率矩阵PM，PM直接由m_population而来，m_populaiton本身有记录最优解的功能
	void setPopRan();//黑方固定情况下，将种群所有的红方单位随机置于地图中 set population randomly
	void setPopUni();//以八连通方式随机生成种群的阵型
	const Point getPMPoint();
	const double getAverageFit();//获取种群平均适应值Fitness
	void showPM();
};
#endif