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
/*
int main() {
	for (int i = 0; i < 10000; i++)
		cout << normalDist() << '\n';
		for (int i = 0; i < 10000; i++)
		cout << exponentialDist(2) << '\n';
	_getch();

	return 0;
}*/

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
		//qwe
		if (server)
			downTime = downTime + timeTact - t1;
	}
	show();
	double avgQue = queSum / counter;
	cout << "\nINFO\n"<< "Count: "<< counter << "\nqueCount: " << queCount << "\nqueElemSum: " << queSum<< "\navgQue: " << avgQue << "\ndownTime: "<< downTime << endl;
	//_getch();
	//cin >> counter;
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
	double x, y, h;
	do 
	{
		x = -5.0 + 10.0 * randomize();
		y = (1.0 / sqrt(2.0 * M_PI)) * exp((-1.0 * pow(x, 2.0)) / 2.0);
		h = 0.4 * randomize();
	} while (h > y);
	return mean + sigma * x;
}
double exponentialDist(double lambda)
{
	//NO 0-1 
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