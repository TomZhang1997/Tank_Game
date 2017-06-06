/*
如果改变战场大小，需要改变的代码有：
1.population构造函数的种群大小以及PM的size
2.PM矩阵的附加值e
3.PM矩阵选点范围
4.最初随机生成编队时的规模大小，setpopoRan,setpopUni
5.八联通生成的越界检查
*/

#include<iostream>
using namespace std;
#include"Population.h"//种群类已经间接包含管理、坦克、点类
int main() {
	vector<Tank> red;
	vector<Tank> black;
	double AverageFit[50];//记录种群平均适应值Fitness的数组
	int FitPos = 0;
	bool ifContinueEvolution = 1;
	//添加黑色方列阵
	Tank temp(Point(4,4));
	for (int i = 0; i < 10; i++) {
		temp.setpos(4 + i, 4);
		black.push_back(temp);
	}
	//设置红色方坦克数量
	red.resize(10);
	//随机生成种群
	Tank_Management tempManage(red, black);
	Population tempPop(tempManage);
	tempPop.setPopUni();//随机生成？八联通？
	tempPop.updatePopFitness();
	tempPop.updatePopWeight();
	tempPop.updatePM();//当采用八联通策略时此处崩溃 访问越界！！！！！
	AverageFit[FitPos++] = tempPop.getAverageFit();
	FitPos = FitPos % 50;
	srand(time(0));

	while (ifContinueEvolution == 1) {
		//-------种群进化一代-----
		Point PMRanPoint;
		for (int i = 0; i < tempPop.getPopSize(); i++) {
			//把种群的某一个阵型拷贝给backup备份（留作比较）
			tempPop.reBackup() = tempPop.rePopulation()[i];
			for (int j = 0; j < tempPop.reBackup().reRed().size(); j++) {
				if ((rand() % 101) / 100.0 < 0.5)continue;
				else {
					PMRanPoint = tempPop.getPMPoint();
					if (tempPop.reBackup().ifOverlap(PMRanPoint) == 0)tempPop.reBackup().reRed()[j].setpos(PMRanPoint);
					else continue;
					tempPop.reBackup().updateFitness();
					if (tempPop.reBackup().reFitness() > tempPop.rePopulation()[i].reFitness())tempPop.rePopulation()[i] = tempPop.reBackup();
					if (tempPop.reBackup().reFitness() == tempPop.rePopulation()[i].reFitness())
						if (rand() % 2 == 1)tempPop.rePopulation()[i] = tempPop.reBackup();
				}//else结尾
			}//j循环结尾
		}//i循环结尾
		//--------一代进化完毕-----
		ifContinueEvolution = 0;
		tempPop.updatePopWeight();
		tempPop.updatePM();
		AverageFit[FitPos++] = tempPop.getAverageFit();
		if (FitPos == 50)cout << "进化了50代" << endl;
		FitPos = FitPos % 50;
		for (int i = 0; i < 50; i++)if (AverageFit[i] != AverageFit[0]) { ifContinueEvolution = 1; break; }
	}
	//种群进化完毕，输出概率矩阵
	tempPop.showPM();
	system("pause");
	return 0;
}