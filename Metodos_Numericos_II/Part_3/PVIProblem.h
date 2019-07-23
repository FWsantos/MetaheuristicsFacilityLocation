#include "Eigen/Dense"
#include "Eigen/LU"
#include <cmath>
#include <iostream>
using namespace Eigen;

using namespace std;

const int matricula[] = {3,9,9,3,4,6};
class PVIProblem{
private:
	char* expressao;
	double f(double* S); // S = [Y, t]
	VectorXd f(double t, VectorXd S); 
	double norma(VectorXd X1, VectorXd X2);

public:
	// PVIProblem(char* expressao);
	double* eulerForward(double* S0, double h, double t);
	VectorXd RungeKutta(VectorXd S0, double h, double t, double erro);

};