#include "Part_2/EigenProblem.cpp"

void questao1(MatrixXd A){
	// int matricula;
	// cout << "Insira a matricula> ";
	// cin >> matricula;

	cout << "Questao 01"<<endl<<endl;
	VectorXd x(5);
	double e = 0.0000001;
	x << 1,1,1,1,1;
	EigenProblem *p = new EigenProblem();
	cout << "A" <<endl<< A<<endl;
	cout << "x" <<endl<< x<<endl;
	cout << "erro = " << e<<endl;

	cout << "-------Regular Power-----------"<<endl;
	p->regularPower(A, e, x);
	double a = p->getEValue();
	cout <<"Maior Auto valor"<< endl<< a <<endl;
	// cout <<"Auto vetor"<< endl<< p->getEVector() <<endl;
	// cout << "A*x" << endl << A*p->getEVector() <<endl;
	// cout << "lambda*x" << endl << p->getEValue()*p->getEVector() <<endl;

	cout << "-------Reverse Power-----------"<<endl;
	p->reversePower(A, e, x);
	double b =  p->getEValue();
	cout <<"Menor Auto valor"<< endl<< b <<endl;
	// cout <<"Auto vetor"<< endls<< p->getEVector() <<endl;
	// cout << "A*x" << endl << A*p->getEVector() <<endl;
	// cout << "lambda*x" << endl << p->getEValue()*p->getEVector() <<endl;

	cout << "k(A) = "<< abs(a)/abs(b);

}

void questao2(MatrixXd A){
	cout << "Questao 02"<<endl<<endl;
	EigenProblem *p = new EigenProblem();
	int passos = 200;
	double erro = 0.000000000000009;

	MatrixXd AAT = A*A.transpose();
	cout << endl << "[A * AT]: "<<endl<<AAT<<endl;
	p->jacobi(AAT, erro, passos);
	cout << "Jacobi para erro de"<< erro <<" e ate "<<passos<<" iteracoes."<<endl;
	MatrixXd U = p->getEVectors();
	cout <<endl<< "Matriz U: "<< endl <<U<<endl;

	MatrixXd E = p->getEValues().asDiagonal();
	for (int i = 0; i < E.rows(); ++i)
		E(i,i) = sqrt(E(i,i));

	MatrixXd ATA = A.transpose()*A;
	cout << endl << "[AT * A]: "<<endl<<ATA<<endl;
	p->QR(ATA, erro, passos);
	cout << "QR para erro de"<< erro<<" e ate "<<passos<<" iteracoes."<<endl;
	MatrixXd V = p->getEVectors();
	cout <<endl<< "Matriz V: "<< endl <<V<<endl;

	for (int i = 0; i < A.cols(); ++i){
		if(V(0,i) < 0)
			V.col(i) = -1*V.col(i);
		if(U(0,i) < 0)
			U.col(i) = -1*U.col(i);
	}

	// cout <<"sigma: "<<endl<< E<<endl;
	cout << "Decomposicao SVD: "<<endl;
	cout <<"U = "<<endl<< U<<endl;	
	cout <<"sigma = "<<endl<< E<<endl;	
	cout <<"VT = "<<endl<< V.transpose()<<endl;	

	cout << "A = U*sigma*VT = "<<endl;
	MatrixXd A_test;

	// A_test = U*E*V.transpose();
	A_test = U*E*V.transpose();
	// A_test = U*A_test;
	cout << A_test<<endl;
	cout << endl<<"A"<<endl;
	cout << endl<<A<<endl;
}

void questao3(MatrixXd A){
	cout << "Questao 03"<<endl<<endl;
	EigenProblem *p = new EigenProblem();
	int passos = 200;
	double erro = 0.000000000000009;

	MatrixXd AAT = A*A.transpose();
	cout << endl << "[A * AT]: "<<endl<<AAT<<endl;
	p->jacobi(AAT, erro, passos);
	cout << "Jacobi para erro de"<< erro <<" e ate "<<passos<<" iteracoes."<<endl;
	MatrixXd U = p->getEVectors();
	cout <<endl<< "Matriz U: "<< endl <<U<<endl;


	MatrixXd ATA = A.transpose()*A;
	cout << endl << "[AT * A]: "<<endl<<ATA<<endl;
	p->QR(ATA, erro, passos);
	cout << "QR para erro de"<< erro<<" e ate "<<passos<<" iteracoes."<<endl;
	MatrixXd V = p->getEVectors();
	cout <<endl<< "Matriz V: "<< endl <<V<<endl;

	MatrixXd E = p->getEValues().asDiagonal();
	E = E.block(0,0,A.rows(),A.cols());
	for (int i = 0; i < E.rows(); ++i)
		E(i,i) = sqrt(E(i,i));
	cout << endl<<"sigma: "<<endl<<E<<endl;
	for (int i = 0; i < V.cols(); ++i)
		if(V(0,i) < 0)
			V.col(i) = -1*V.col(i);

	for (int i = 0; i < U.cols(); ++i)
		if(U(0,i) < 0)
			U.col(i) = -1*U.col(i);

	// cout <<"sigma: "<<endl<< E<<endl;
	cout << "Decomposicao SVD: "<<endl;
	cout <<"U = "<<endl<< U<<endl;	
	cout <<"sigma = "<<endl<< E<<endl;	

	// cout <<"VT = "<<endl<< V<<endl;	
	cout <<"VT = "<<endl<< V.transpose()<<endl;	

	cout << "A = U*sigma*VT = "<<endl;
	MatrixXd A_test;

	A_test = U*E*V.transpose();
	// A_test = U*E;
	// // A_test = A_test*V.transpose();
	cout << A_test<<endl;
	cout << endl<<"A"<<endl;
	cout << endl<<A<<endl;	
}

int main(){

	int matricula[6];
	// char abc[] = {'A', 'B', 'C', 'D', 'E', 'F'};
	// cout << "Insira Matricula: "<<endl;
	// for (int i = 0; i < 6; ++i){
	// 	cout << abc[i]<<"> ";
	// 	cin >> matricula[i];
	// }
	// 399346
	// 400909
	MatrixXd A(5,5);
	A << 39,3,9,9,3,3,23,4,6,12,9,4,62,18,12,9,6,18,37,7,3,12,12,7,51;
	// A(0,0) = 30+matricula[0]+matricula[5];
	// A(1,1) = 10+matricula[1]+matricula[4];
	// A(2,2) = 50+matricula[2]+matricula[3];
	// A(3,3) = 40-matricula[0];
	// A(4,4) = 60-matricula[1];
	// for (int i = 0; i < 4; ++i){
	// 	A(0,i+1) = matricula[i];
	// 	A(i+1, 0) = A(0,i+1);
	// }

	// A(1,2) = matricula[4];
	// A(2,1) = matricula[4];

	// A(1,3) = matricula[5];
	// A(3,1) = matricula[5];


	// A(1,4) = matricula[0]+matricula[1];
	// A(4,1) = matricula[0]+matricula[1];

	// A(2,3) = matricula[1]+matricula[2];
	// A(3,2) = matricula[1]+matricula[2];

	// A(2,4) = matricula[2]+matricula[3];
	// A(4,2) = matricula[2]+matricula[3];

	// A(3,4) = matricula[3]+matricula[4];
	// A(4,3) = matricula[3]+matricula[4];

	questao1(A);
	questao2(A);
	questao3(A.block(0,0,3,5));
	return 0;
}