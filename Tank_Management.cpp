#include"Tank_Managementh.h"
Tank_Management::Tank_Management():m_fitness(0),m_normalFitness(0),m_weight(0){}
Tank_Management::Tank_Management(const vector<Tank>& red, const vector<Tank>& black):m_red(red),m_black(black),m_fitness(0),m_normalFitness(0),m_weight(0){}
vector<Tank>& Tank_Management::reRed() { return m_red; }
vector<Tank>& Tank_Management::reBlack() { return m_black; }
double& Tank_Management::reFitness() { return m_fitness; }
double& Tank_Management::reNorFit() { return m_normalFitness; }
double& Tank_Management::reWeight() { return m_weight; }
bool Tank_Management::ifOverlap(const int& x, const int& y) {
	int i = 0;
	for (i = 0; i < m_red.size(); i++) 
		if (m_red[i].rePos().getX() == x&&m_red[i].rePos().getY() == y)return 1;
	for (i = 0; i < m_black.size(); i++)
		if (m_black[i].rePos().getX() == x&&m_black[i].rePos().getY() == y)return 1;
	return 0;
}
bool Tank_Management::ifOverlap(const Point&pos) {
	int i = 0;
	for (i = 0; i < m_red.size(); i++)
		if (m_red[i].rePos().getX() == pos.getX()&&m_red[i].rePos().getY() == pos.getY())return 1;
	for (i = 0; i < m_black.size(); i++)
		if (m_black[i].rePos().getX() == pos.getX()&&m_black[i].rePos().getY() == pos.getY())return 1;
	return 0;
}
void Tank_Management::updateFitness() {
	vector<Tank> tempRed = m_red;
	vector<Tank>tempBlack = m_black;
	double redOri = tempRed.size(), blackOri = tempBlack.size();
	bool ifTar = 0;
	int i = 0, j = 0;
	for (i = 0; i < tempRed.size()&&ifTar==0; i++) {
		for (j = 0; j < tempBlack.size(); j++) {
			if (tempRed[i].distance(tempBlack[j]) <= tempRed[i].getAtaDistance()) { ifTar = 1; break; }
		}
	}
	for (i = 0; i < tempBlack.size() && ifTar == 0; i++) {
		for (j = 0; j < tempRed.size(); j++) {
			if (tempBlack[i].distance(tempRed[j]) <= tempBlack[i].getAtaDistance()) { ifTar = 1; break; }
		}
	}
	while(ifTar==1){//双方互打一轮
		srand(time(0));
		int tar = 0;
		vector<int> temp;//存放范围内敌方目标编号
						 //红方所有单位攻击
		for (i = 0; i < tempRed.size(); i++) {
			for (j = 0; j < tempBlack.size(); j++) {
				if (tempRed[i].distance(tempBlack[j]) <= tempRed[i].getAtaDistance())temp.push_back(j);
			}
			if (temp.size() == 0)continue;
			tar = temp[rand() % temp.size()];
			tempRed[i].atack(tempBlack[tar]);
			temp.clear();
		}
		//黑方所有单位攻击
		for (i = 0; i < tempBlack.size(); i++) {
			for (j = 0; j < tempRed.size(); j++) {
				if (tempBlack[i].distance(tempRed[j]) <= tempBlack[i].getAtaDistance())temp.push_back(j);
			}
			if (temp.size() == 0)continue;
			tar = temp[rand() % temp.size()];
			tempBlack[i].atack(tempRed[tar]);
			temp.clear();
		}
		//清理死亡单位
		for (i = 0; i < tempRed.size(); i++)if (tempRed[i].getHp() <= 0)  tempRed.erase(tempRed.begin() + i);
		for (i = 0; i < tempBlack.size(); i++)if (tempBlack[i].getHp() <= 0)   tempBlack.erase(tempBlack.begin() + i);
		//-------------一轮攻击结束--------
		ifTar = 0;//开关置为0
		//--------------再次搜索敌人--------
		for (i = 0; i < tempRed.size()&&ifTar==0; i++) {
			for (j = 0; j < tempBlack.size(); j++) {
				if (tempRed[i].distance(tempBlack[j]) <= tempRed[i].getAtaDistance()) { ifTar = 1; break; }
			}
		}
		for (i = 0; i < tempBlack.size() && ifTar == 0; i++) {
			for (j = 0; j < tempRed.size(); j++) {
				if (tempBlack[i].distance(tempRed[j]) <= tempBlack[i].getAtaDistance()) { ifTar = 1; break; }
			}
		}
	}//while结尾，一轮攻击结束
	m_fitness = (blackOri - tempBlack.size()) / redOri - (redOri - tempRed.size()) / blackOri;
	return;
}


