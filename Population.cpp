#include"Population.h"
#include<iomanip>
//------------这里在创建种群时默认18*10，双方各10单位----------------
//------------种群个体总数为60
Population::Population(const Tank_Management& TankManage) {
	m_population.resize(60, TankManage);
	m_PM.resize(18, vector<double>(10, 0));
	m_backup = TankManage;
	return;
}

Tank_Management& Population::reBackup() { return m_backup; }

vector<Tank_Management>& Population::rePopulation() { return m_population; }

const int Population::getPopSize() { return m_population.size(); }

void Population::updatePopFitness() {
	for (int i = 0; i < m_population.size(); i++)m_population[i].updateFitness();
	return;
}

void Population::updatePopWeight() {
	const double e = 2.71828;
	double max = m_population[0].reFitness(), min = max;
	for (int i = 1; i < m_population.size(); i++) {
		if (m_population[i].reFitness()>max)max = m_population[i].reFitness();
		if (m_population[i].reFitness()<min)min = m_population[i].reFitness();
	}
	for (int j = 0; j < m_population.size(); j++) {
		m_population[j].reNorFit() = (m_population[j].reFitness() - min + 1) / (max - min + 1);
	}
	for (int i = 0; i < m_population.size(); i++) {
		m_population[i].reWeight() = 1 / (1 + pow(e, -m_population[i].reNorFit()));
	}
	return;
}

void Population::updatePM() {
	int i = 0, j = 0, x = 0, y = 0;
	for (i = 0; i < m_PM.size();i++) {
		for (j = 0; j < m_PM[i].size(); j++) {
			m_PM[i][j] = 0.001333;
		}
	}
	for (i = 0; i < m_population.size(); i++) {
		for (j = 0; j < m_population[i].reRed().size(); j++) {
			x = m_population[i].reRed()[j].rePos().getX();
			y = m_population[i].reRed()[j].rePos().getY();
			m_PM[x][y] += m_population[i].reWeight();
		}//j循环结尾
	}//i循环结尾
	return;
}
void Population::setPopRan() {
	int i = 0,j = 0;
	//先将种群中所有红方单位设定在一个不可能重合的地方
	for ( i = 0; i < m_population.size(); i++) {
		for (j = 0; j < m_population[i].reRed().size(); j++) {
			m_population[i].reRed()[j].setpos(-1, -1);
		}//j循环
	}//i循环
	srand(time(0));
	int tempx = rand()%18, tempy = rand()%10;
	for (i = 0; i < m_population.size(); i++) {
		for (j = 0; j < m_population[i].reRed().size(); j++) {
			while (m_population[i].ifOverlap(tempx, tempy) == 1) {
				tempx = rand() % 18, tempy = rand() % 10;
			}//while
			m_population[i].reRed()[j].setpos(tempx,tempy); 
			tempx = rand() % 18, tempy = rand() % 10;
		}//j
	}//i
}//函数结尾

const Point Population::getPMPoint() {
	double sum = 0,randNum = 0,addNum = 0;
	int i = 0, j = 0;
	for (i = 0; i < m_PM.size(); i++) {
		for (j = 0; j < m_PM[i].size(); j++) {
			sum += m_PM[i][j];
		}
	}
	srand(time(0));
	randNum = (rand() % 100001)/100000.;
	while (1) {
		for (i = 0; i < m_PM.size(); i++) {
			for (j = 0; j < m_PM[i].size(); j++) {
				addNum += m_PM[i][j] / sum;
				if (addNum >= randNum)return Point(i, j);
			}
		}
		addNum = 0;
	}
	
}
const double Population::getAverageFit() {
	double ave = 0;
	for (int i = 0; i < m_population.size(); i++) {
		ave += m_population[i].reFitness();
	}
	ave /= m_population.size();
	return ave;
}

void Population::showPM() {
	int i = 0, j = 0;
	cout << "PM is as follow" << endl;
	for (i = 0; i < m_PM.size(); i++) {
		for (j = 0; j < m_PM[i].size(); j++) {
			cout << setw(10) << m_PM[i][j];
		}
		cout << endl;
	}
	cout << "PM output end." << endl;
	return;
}
void Population::setPopUni() {
	int arr[3] = { 1,-1,0 };
	int incX = 0, incY=0,randCounter=0;
	int i = 0, j = 0;
	for (i = 0; i < m_population.size(); i++) {
		for (j = 0; j < m_population[i].reRed().size(); j++) {
			m_population[i].reRed()[j].setpos(-1, -1);
		}//j循环
	}//i循环
	srand(time(0));
	int tempx , tempy ;
	//-----对每一个个体循环
	for (i = 0; i < m_population.size(); i++) {
		//-----随机出第一个点
		tempx = rand() % 18;
		tempy = rand() % 10;
		while (m_population[i].ifOverlap(tempx, tempy)) {
			tempx = rand() % 18;
			tempy = rand() % 10;
		}
		m_population[i].reRed()[0].setpos(tempx, tempy);
		//------根据八连通随机生成剩下的位置
		for (j = 1; j < m_population[i].reRed().size(); j++) {
			incX = arr[rand() % 3];
			incY = arr[rand() % 3];
			while (m_population[i].ifOverlap(tempx+incX, tempy+incY)||tempx+incX<0||tempx+incX>=18||tempy+incY<0||tempy+incY>=10) {
				incX = arr[rand() % 3];
				incY = arr[rand() % 3];
				++randCounter;
				if (randCounter == 20) { arr[0] += 1; arr[1] -= 1; randCounter = 0; }
			}
			randCounter = 0;
			arr[0] = 1; arr[1] = -1;
			m_population[i].reRed()[j].setpos(tempx + incX, tempy + incY);
			tempx += incX;
			tempy += incY;
			if (tempx >= 18 || tempx < 0)cout << "X out of range" << endl;
			if (tempy >= 10 || tempy < 0)cout << "Y out of range" << endl;
		}//放置之后agent的for
	}//对种群for循环的结尾
	return;
}