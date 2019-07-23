#include "Part_3/PVIProblem.cpp"
// #in


void questao1(){

	VectorXd S0(2);
	// cout << matricula[5];
	S0(0) = (matricula[4]+matricula[5])%3;
	S0(1) = 0;
	// cout << S0<<endl;
	PVIProblem *p = new PVIProblem();
	VectorXd R;
	R = p->RungeKutta(S0, 0.1, 1.2, 0.001);
	cout << "Runge-Kutta 4 ordem. h = "<<0.1<<", erro = "<<0.001<<", t = "<<1.2<<", S0 transposto = "<<S0.transpose()<<endl;

	cout << "x(1.2) = "<<R(0)<<endl;
	cout << "y(1.2) = "<<R(1)<<endl;

}

void questao2(){
	const double N = 4 + (matricula[0]+matricula[1]+matricula[2]+matricula[3]+matricula[4]+matricula[5])%4;
	const double T = (matricula[0]+matricula[1]+matricula[2]);
	const double P = (matricula[3]+matricula[4]+matricula[5]);
	const double delta_r = (0.5-0.2)/N;
	double r[] = {0.2+delta_r, 0.2+2*delta_r, 0.2 + 3*delta_r};

	cout << "N = "<<N<<endl;
	cout << "T = "<<T<<endl;
	cout << "P = "<<P<<endl;
	cout << "delta_r = "<<delta_r<<endl;
	for (int i = 0; i < 3; ++i){
		cout << "r"<<i<<" = "<<r[i]<<endl;
	}
	const double result = -P/T;
	cout <<"-P/T = "<<result<<endl;
	MatrixXd A(3,3);
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if(i == j){
				A(i,j) = -2/pow(delta_r, 2);
			}else if(j == i+1){
				A(i,j) = (1/pow(delta_r, 2))+ 1/((2*delta_r*r[i]));
			}else if(j == i-1){
				A(i,j) = (1/pow(delta_r, 2))- 1/((2*delta_r*r[i]));
			}
		}
	}


	cout<< "\nA = \n"<< A<< endl;

	VectorXd y = VectorXd::Constant(3, result);
	cout << "\nb = \n"<<y<<endl;
	y = A.fullPivLu().solve(y);
	cout << "\ny = \n"<< y <<endl;
	cout << "\nA*y = \n"<< A*y<<endl;
}
int main(int argc, char const *argv[])
{
	// questao1();
	questao2();
	// int matricula[] = {3,9,9,3,4,6};

	return 0;
}