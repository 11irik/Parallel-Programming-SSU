// conveyor-transformer.cpp 
// compile with: /EHsc
#include <agents.h>
#include <cmath>
#include <iostream>
#include <locale.h>
#include <time.h>

using namespace concurrency;
using namespace std;

int const N = 100; //����������� �����
int const NNN = 1000; //����� ������� �� ����� ��������� 
int const Chunk = 100; //������ �������������� ���������

double Func1(double x)//������ ������� ���������
{
	double Tmp = 0, Tmpa=abs(x);
	for (int n = 0; n <= N; n++){
		double Tmpxn = x + n, Tmpn3 = n*n*n;
		for (int k = 0; k <= N; k++){
			double Tmpk = k*k;
			for (int j = 0; j <= N; j++)
				Tmp += Tmpxn / (1 + Tmpa + Tmpn3 + k*k + j*j);
		}
	}
	return Tmp;
}

double Func2(double x)//������ ������� ���������
{
	double Tmp = 0, Tmpa=abs(x);
	for (int n = 0; n <= N; n++){
		double Tmpn = n*n; 
		for (int k = 0; k <= N; k++){
			double Tmpk = k*k*k;
			for (int j = 0; j <= N; j++)
				Tmp += 1.0 / (1 + Tmpa + Tmpn + Tmpk + j*j);
		}
	}
	return x*Tmp;
}

double Func3(double x)//������ ������� ���������
{
	double Tmp = 0, Tmp2 = x*x;
	for (int n = 0; n <= N; n++){
		double Tmpn = n*n;
		for (int k = 0; k <= N; k++){
			double Tmpk = k*k;
			for (int j = 0; j <= N; j++)
				Tmp += (Tmp2 + j) / (1 + Tmp2 + Tmpn + Tmpk + j*j*j);
		}
	}
	return Tmp;
}

double Func4(double x)//��������� ������� ���������
{
	double Tmp = 0, Tmpa=abs(x);
	for (int n = 0; n <= N; n++){
		double Tmpn = n*n*n;
		for (int k = 0; k <= N; k++){
			double Tmpk = Tmpa - k, 
				Tmpk4 = k*k; Tmpk4 *= Tmpk4;
			for (int j = 0; j <= N; j++)
				Tmp += Tmpk / (1 + Tmpa + Tmpn + Tmpk4 + j*j*j);
		}
	}
	return Tmp;
}



int main()
{
	setlocale(LC_ALL, ".ACP");
	vector<double> X(NNN), Y(NNN), Z(NNN);
	//���������� �������� �������
	for (int k = 0; k < X.size(); k++)
		X[k] = 10 * sin((double)k);
	double Tms = clock();
	//���������������� ����������
	for (int k = 0; k < X.size(); k++){
		Y[k] = Func1(X[k]);
		Y[k] = Func2(Y[k]);
		Y[k] = Func3(Y[k]);
		Y[k] = Func4(Y[k]);
	}
	Tms = (clock() - Tms) / CLOCKS_PER_SEC;
	cout << "����� ����������������� ���������: " << Tms << " c." << endl;
    //������� ���������
	// t1 -> t2 -> t3 -> t4
	transformer<double, double> t1(Func1), t2(Func2), t3(Func3), t4(Func4);
	t1.link_target(&t2);
	t2.link_target(&t3);
	t3.link_target(&t4);
		
	Tms = clock();
	//������������ ����������
	for (int k = 0; k < Chunk; k++)
		send(t1, X[k]);
	
	for (int k = Chunk; k < X.size(); k++){
		Z[k-Chunk] = receive(t4);
		send(t1, X[k]);
	}
	for (int k = X.size()-Chunk; k < X.size(); k++){
		Z[k] = receive(t4);
	}
	Tms = (clock() - Tms) / CLOCKS_PER_SEC;
	cout << "����� ������������� ���������: " << Tms << " c." << endl;

}
