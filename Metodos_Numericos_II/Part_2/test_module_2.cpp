// #include <iostream>
#include "EigenProblem.cpp"
// using namespace std;

void testePotencia(){

	MatrixXd A(3,3);
	A << 1,3,-1,3,2,4,-1,4,10;
	VectorXd x(3);
	double e = 0.000001;
	x << -1,0,1;
	EigenProblem *p = new EigenProblem();
	cout << "A" <<endl<< A<<endl;
	cout << "x" <<endl<< x<<endl;
	cout << "erro = " << e<<endl;

	cout << "-------Regular Power-----------"<<endl;
	p->regularPower(A, e, x);
	double a =  p->getEValue();
	cout <<"Auto valor"<< endl<< p->getEValue() <<endl;
	cout <<"Auto vetor"<< endl<< p->getEVector() <<endl;
	cout << "A*x" << endl << A*p->getEVector() <<endl;
	cout << "lambda*x" << endl << p->getEValue()*p->getEVector() <<endl;

	cout << "-------Reverse Power-----------"<<endl;
	p->reversePower(A, e, x);
	double b =  p->getEValue();
	cout <<"Auto valor"<< endl<< p->getEValue() <<endl;
	cout <<"Auto vetor"<< endl<< p->getEVector() <<endl;
	cout << "A*x" << endl << A*p->getEVector() <<endl;
	cout << "lambda*x" << endl << p->getEValue()*p->getEVector() <<endl;

	cout << "-------Shift Power-----------"<<endl;
	p->shiftPower(A, e, x, (a+b)/2);
	cout <<"Auto valor"<< endl<< p->getEValue() <<endl;
	cout <<"Auto vetor"<< endl<< p->getEVector() <<endl;
	cout << "A*x" << endl << A*p->getEVector() <<endl;
	cout << "lambda*x" << endl << p->getEValue()*p->getEVector() <<endl;
}

void testeTridiagonal(){
	MatrixXd A(4,4);
	A << 1.36, -0.48, -1, 0, -0.48, 1.64, 0, 0,-1,0,1.36,0.48,0,0,0.48,1.64;
	cout << A << endl;

	EigenProblem *p = new EigenProblem();
	MatrixXd R = p->househoder(A);
	cout << R<<endl;
}

void testeJacobi(){
	MatrixXd A(3,3);
	A << 2, -1, 0, -1, 2, -1, 0, -1, 2;
	// A << 1, 3, -1, 3, 2, 4, -1, 4, 10;
	cout << A << endl;

	EigenProblem *p = new EigenProblem();
	p->jacobi(A, 0.01, 20);
	VectorXd R = p->getEValues();
	cout<< "-----------------------------------------------------\n\n";
	cout << R<<endl;

	cout<< "-----------------------------------------------------\n\n";
	MatrixXd T = p->getEVectors();
	cout << T<<endl;

	// cout<< "-----------------------------------------------------\n\n";
	// cout << A*T<<endl;
	// cout<< "-----------------------------------------------------\n\n";
	// cout << R*T<<endl;
}

void testeQR(){
	MatrixXd A(3,3);
	A << 2, -1, 0, -1, 2, -1, 0, -1, 2;
	cout << A << endl;

	EigenProblem *p = new EigenProblem();
	p->QR(A, 0.01, 20);
	VectorXd R = p->getEValues();
	cout<< "-----------------------------------------------------\n\n";
	cout << R<<endl;

	cout<< "-----------------------------------------------------\n\n";
	MatrixXd T = p->getEVectors();
	cout << T<<endl;

	MatrixXd B = R.asDiagonal()	;
	cout << "B" << B<<endl;
}

int main()
{
	// testeTridiagonal();
	testeJacobi();
	cout << endl<<endl;
	testeQR();
	return 0;
}	