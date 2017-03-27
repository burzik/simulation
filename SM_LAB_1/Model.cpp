#include <iostream>
#include <conio.h>
#include <algorithm>
#include <iomanip>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

double erlangDist();
double poissonDist();
double normalDist();
double exponentialDist(double lambda);
double randomize();
void show();
unsigned int LecureRand();

double counter = 0;
double queCount = 0;
double queSum = 0;
double timeTact = 0;
double timeEnd = 500;
double l1 = erlangDist();
double l2 = poissonDist();
double h = timeEnd + 1;
bool server = true;
int que = 0;
double minVal;
double downTime = 0;
double t1 = 0, t2;
int *queArr = new int[255];

unsigned int pRnd_1 = 0;
unsigned int pRnd_2 = 0;
unsigned int LECURE_RAND_MAX = pow(2, 31) - 1;

int main()
{
	srand(time(NULL));
	cout << "eve: S  ";
	while (timeEnd != 501)
	{
		counter++;
		show();
		//_getch();

		minVal = min({ l1, l2, h, timeEnd });
		timeTact = minVal;
		cout << "eve: ";
		
		if (minVal == timeEnd)
		{
			cout << "END  ";
			downTime = downTime + timeTact - t1;
			timeEnd++;
		}
		if (minVal == l1)
		{
			cout << "l1 ";
			if (server)
			{
				server = false;
				h = minVal + normalDist();
				t1 = minVal;
			}
			else 
			{
				queArr[que] = 1;
				que++;
				queCount++;
				queSum += que;
			}
			l1 = minVal + erlangDist();
		}
		if (minVal == l2)
		{
			cout << "l2 ";
			if (server)
			{
				server = false;
				h = minVal + exponentialDist(2);
				t1 = minVal;
			}
			else
			{
				queArr[que] = 2;
				que++;
				queCount++;
				queSum += que;
			}
			l2 = minVal + poissonDist();
			
		}
		if (minVal == h)
		{
			cout <<"h  ";
			if (que == 0)
			{
				h = 501;
				server = true;
			}
			else
			{
				que--;
				if (queArr[0] == 1)
				{
					//FIFO
					for (int i = 0; i < que; i++)
						queArr[i] = queArr[i+1];
					h = minVal + normalDist();
				}
				else
				{
					for (int i = 0; i < que; i++)
						queArr[i] = queArr[i + 1];
					h = minVal + exponentialDist(2);
				}
			}
		}
		if (server)
			downTime = downTime + timeTact - t1;
	}
	show();
	double avgQue = queSum / counter;
	cout << "\nINFO\n"<< "Count: "<< counter << "\nqueCount: " << queCount << "\nqueElemSum: " << queSum<< "\navgQue: " << avgQue << "\ndownTime: "<< 500 - downTime << endl;
	_getch();
	return 0;
}

double erlangDist()
{
	double num = 0;
	double lambda = 0.25;
	int l = 3;
	for (int i = 0; i < l; i++)
	{
		num += exponentialDist(lambda);
	}
	return num;
}
double poissonDist()
{
	double lambda = 0.5;
	return exponentialDist(lambda);
}
double normalDist()
{
	double mean = 12.0;
	double sigma = 2.0;
	const double a = (8 * (M_PI - 3)) / (3 * M_PI * (4 - M_PI));
	double x = 2 * randomize() - 1;
	double sign = -std::signbit(x) * 2 + 1;
	double errF_i = sign * sqrt(sqrt(pow(2 / (M_PI * a) + log(1 - x * x) / 2, 2) - log(1 - x * x) / a) -
		(2 / (M_PI * a) + log(1 - x * x) / 2));
	return mean + sigma * (sqrt(2) * errF_i);
}
double exponentialDist(double lambda)
{
	double num = (-1.0 / lambda)*log(1.0 - randomize());
	return num;
}

double randomize()
{
	return ((double)(rand()) / (double)RAND_MAX);
}

void show()
{
	cout << setw(5) << "|TT: " << setw(8) << timeTact << left << " | L1: " << setw(8) << l1 << left << " | L2: "
		<< setw(8) << l2 << left << " | h: " << setw(8) << h << left << " | S: " << server << " |Q: " << que;
	cout << " Que: ";
	if (que == 0)
		cout << "N ";
	for (int i = 0; i < que; i++)
		cout << queArr[i] << " ";
	cout << endl;
}


unsigned int PseudoRand1() {
	return pRnd_1 = (1103515245 * pRnd_1 + 12345) % LECURE_RAND_MAX;
}

unsigned int PseudoRand2() {
	return pRnd_2 = (16807 * pRnd_2 + 0) % LECURE_RAND_MAX;
}

unsigned int LecureRand() {
	return (PseudoRand1() - PseudoRand2()) % LECURE_RAND_MAX;
}