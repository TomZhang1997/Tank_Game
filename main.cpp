/*
����ı�ս����С����Ҫ�ı�Ĵ����У�
1.population���캯������Ⱥ��С�Լ�PM��size
2.PM����ĸ���ֵe
3.PM����ѡ�㷶Χ
4.���������ɱ��ʱ�Ĺ�ģ��С��setpopoRan,setpopUni
5.����ͨ���ɵ�Խ����
*/

#include<iostream>
using namespace std;
#include"Population.h"//��Ⱥ���Ѿ���Ӱ�������̹�ˡ�����
int main() {
	vector<Tank> red;
	vector<Tank> black;
	double AverageFit[50];//��¼��Ⱥƽ����ӦֵFitness������
	int FitPos = 0;
	bool ifContinueEvolution = 1;
	//��Ӻ�ɫ������
	Tank temp(Point(4,4));
	for (int i = 0; i < 10; i++) {
		temp.setpos(4 + i, 4);
		black.push_back(temp);
	}
	//���ú�ɫ��̹������
	red.resize(10);
	//���������Ⱥ
	Tank_Management tempManage(red, black);
	Population tempPop(tempManage);
	tempPop.setPopUni();//������ɣ�����ͨ��
	tempPop.updatePopFitness();
	tempPop.updatePopWeight();
	tempPop.updatePM();//�����ð���ͨ����ʱ�˴����� ����Խ�磡��������
	AverageFit[FitPos++] = tempPop.getAverageFit();
	FitPos = FitPos % 50;
	srand(time(0));

	while (ifContinueEvolution == 1) {
		//-------��Ⱥ����һ��-----
		Point PMRanPoint;
		for (int i = 0; i < tempPop.getPopSize(); i++) {
			//����Ⱥ��ĳһ�����Ϳ�����backup���ݣ������Ƚϣ�
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
				}//else��β
			}//jѭ����β
		}//iѭ����β
		//--------һ���������-----
		ifContinueEvolution = 0;
		tempPop.updatePopWeight();
		tempPop.updatePM();
		AverageFit[FitPos++] = tempPop.getAverageFit();
		if (FitPos == 50)cout << "������50��" << endl;
		FitPos = FitPos % 50;
		for (int i = 0; i < 50; i++)if (AverageFit[i] != AverageFit[0]) { ifContinueEvolution = 1; break; }
	}
	//��Ⱥ������ϣ�������ʾ���
	tempPop.showPM();
	system("pause");
	return 0;
}