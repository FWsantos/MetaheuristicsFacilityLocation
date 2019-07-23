#include "PVIProblem.cpp"
// #include <iostream>
// using namespace std;

void testeEulerForward(){
	double S0[] = {0, 1};

	PVIProblem* p = new PVIProblem();
	double* R = p->eulerForward(S0, 0.1, 1);
	// cout << R[0]<<endl;
	cout << R[1]<<endl;
}

// void testeRunge(){
// 	double S0[] = {0, 1};

// 	PVIProblem* p = new PVIProblem();
// 	double t = 0.1;
// 	for (int i = 0; i < 10; ++i){
// 		double* R = p->RungeKutta(S0, 0.2, t, 0.0001);
// 	// cout << R[0]<<endl;
// 		cout << R[1]<<endl;
// 		t+=0.1;
// 	}
// }

void testeRunge(){
	VectorXd S0(1);
	S0(0) = 1;

	PVIProblem* p = new PVIProblem();
	double t = 0;
	for (int i = 0; i < 10; ++i){
		VectorXd R = p->RungeKutta(S0, 1, t, 0.00001);
	// cout << R[0]<<endl;
		cout << R<<endl;
		t+=0.1;
	}
}
int main(int argc, char const *argv[])
{
	// testeEulerForward();
	testeRunge();
	return 0;
}