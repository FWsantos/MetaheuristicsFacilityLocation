#include "EigenProblem.h"

/*
MatrixXd A  -> Matriz da qual se quer ober o auto valor e o auto vetor
double E    -> erro entre as iterações. Criterio de parada do laço
VectorXd x0 -> vetor que o nosso chute inicial(recomendo vetores com todos os componentes igual a 1)

*/

// Retorna o elemento com maior valor absoluto no vetor
double EigenProblem::maxMagnitude(VectorXd x){
	double a = x.maxCoeff(); // Pega o maior elemento do vetor
	double b = x.minCoeff(); // Pega o menor elemento do vetor

	if(abs(a) > abs(b)) //retorna quem tem maior valor absoluto
		return a;
	return b;
}
// Retorna o autovalor
double EigenProblem::getEValue(){
	return this->eigenValue;
}
// Retorna o autovetor
VectorXd EigenProblem::getEVector(){
	return this->eigenVector;
}
// Metodo da potencia regular
void EigenProblem::regularPower(MatrixXd A, double E, VectorXd x0){
	double value; 
	VectorXd xOld, y, xNew = x0;

	do{
		xOld = xNew;
		y = A*xOld;
		value = maxMagnitude(y); // |value| = ||y||_inf
		xNew = (1/value)*y; // Normalizo o vetor
	}while(abs(maxMagnitude(xOld - xNew)) > E); // checa se ||xold-xnew||_inf é maior que o erro 'E'
	this->eigenValue = value; // Seta o autovalor calculado
	this->eigenVector = xNew; // Seta o autovetor calculado
}
// Metodo da potencia inversa
void EigenProblem::reversePower(MatrixXd A, double E, VectorXd x0){
	MatrixXd iA = A.inverse();// iA -> Inversa da matriz A
	regularPower(iA, E, x0);// chama o metodo regular
	this->eigenValue = 1/this->eigenValue;// Seta o autovalor modificado
}
// Metodo da potencia com deslocamento
void EigenProblem::shiftPower(MatrixXd A, double E, VectorXd x0, double M){
	int d = A.rows();
	MatrixXd A2 =  A - M*MatrixXd::Identity(d,d);// subtrai M da diagonal principal de A
	reversePower(A2, E, x0);// chama o metodo inverso
	this->eigenValue = this->eigenValue+M;// Seta p autovalor modificado

}

MatrixXd EigenProblem::montagemH(MatrixXd A, int i){// Metodo que gera a matriz de holseholder
	int d = A.rows();
	VectorXd v = VectorXd::Zero(d);
	for (int k = i+1; k < d; ++k)
		v(k) = A(k,i);
	
	double l_v = v.norm();
	VectorXd vl = VectorXd::Zero(d);
	vl(i+1) = l_v;

	VectorXd N = v-vl;
	VectorXd n = N.normalized();
	return MatrixXd::Identity(d,d)-2*n*n.transpose();

	return A;
}
// Metodo para obter matriz tri diagonal
MatrixXd EigenProblem::househoder(MatrixXd A){// Metodo para encontrar matriz tridiagonal
	int d = A.rows();
	MatrixXd H = MatrixXd::Identity(d,d);
	MatrixXd Hi;

	for(int i = 0; i < d-2; ++i){
		Hi = montagemH(A, i);
		A = Hi*A*Hi;
		H = H* Hi;
	}
	acumuloH = H;

	return A;	
}

MatrixXd EigenProblem::montagemJ(MatrixXd A, int i, int j){
	const double PI = 3.14159265359;
	int d = A.rows();
	double teta;
	if(A(i,i) != A(j,j))
		teta = atan(2*A(i,j)/(A(i,i)-A(j,j)))/2;
	else
		teta = PI/4;

	MatrixXd Pij = MatrixXd::Identity(d,d); // Recebe a Identidade
	Pij(j,j) = cos(teta);
	Pij(i,i) = cos(teta);
	Pij(i,j) = -sin(teta);
	Pij(j,i) = sin(teta);

	return Pij;
}

// Metodo para obter matriz tri diagonal
void EigenProblem::jacobi(MatrixXd A, double E, int ite){// Metodo para encontrar matriz de autovalores
	int d = A.rows(), j, i; // d =  Dimensao da Matriz A
	eigenVectorMatrix = MatrixXd::Identity(d,d); // Resultado da matriz de holseholder
	MatrixXd P, Pij; // Matriz de cada iteracao

	while(paradaJacobi(A, E) and ite > 0){
		--ite;
		P = MatrixXd::Identity(d,d); // Recebe a Identidade

		for (j = 0; j < d-1; ++j){
			for (i = j+1; i < d; ++i){
				Pij = montagemJ(A, i, j);
				A = Pij.transpose()*A*Pij;
				P = P*Pij;
			}
		}
		eigenVectorMatrix = eigenVectorMatrix*P;
	}
	eigenValues = A.diagonal();
	sortEValues();
}

bool EigenProblem::paradaJacobi(MatrixXd A, double E){
	int d = A.rows(); // d =  Dimensao da Matriz A
	for (int i = 0; i < A.rows(); ++i)
		for (int j = 0; j < A.cols(); ++j)
			if(i != j && abs(A(i,j)) > E)
				return true;
	return false;
}

MatrixXd EigenProblem::getEVectors(){
	return eigenVectorMatrix;
}

VectorXd EigenProblem::getEValues(){
	return eigenValues;
}

void EigenProblem::sortEValues(){
	double max , a;
	int id_max;
	VectorXd aux;

	for (int j = 0; j < eigenValues.size(); ++j){	

		id_max = j;
		max = abs(eigenValues(j));

		for (int i = j; i < eigenValues.size(); ++i){
			if(abs(eigenValues(i)) > max){
				max = eigenValues(i);
				id_max = i;
			}
		}

		a = eigenValues(j);
		eigenValues(j) = eigenValues(id_max);
		eigenValues(id_max) = a;

		aux = eigenVectorMatrix.col(j);
		eigenVectorMatrix.col(j) = eigenVectorMatrix.col(id_max);
		eigenVectorMatrix.col(id_max) = aux;

	}
}


MatrixXd EigenProblem::montagemQR(MatrixXd A, int i, int j){
	const double PI = 3.14159265359;
	int d = A.rows();
	double teta;
	if(A(i,i) != A(j,j))
		teta = atan(A(i,j)/A(j,j));
	else
		teta = PI/2;

	MatrixXd Pij = MatrixXd::Identity(d,d); // Recebe a Identidade
	Pij(j,j) = cos(teta);
	Pij(i,i) = cos(teta);
	Pij(i,j) = -sin(teta);
	Pij(j,i) = sin(teta);

	return Pij;
}
// Metodo de QR
void EigenProblem::QR(MatrixXd A, double E, int ite){
	// P = MatrixXd::Identity(A.rows(), A.cols());

	A = househoder(A);
	int d = A.rows(), j, i; // d =  Dimensao da Matriz A
	// eigenVectorMatrix = MatrixXd::Identity(d,d); // Resultado da matriz de holseholder
	eigenVectorMatrix = acumuloH; // Resultado da matriz de holseholder

	MatrixXd Pij, Q, QT = MatrixXd::Identity(d,d); // Matriz de cada iteracao

	while(paradaJacobi(A, E) && ite > 0){
		// P = MatrixXd::Identity(d,d); // Recebe a Identidade
		QT = MatrixXd::Identity(d,d);
		// Q = MatrixXd::Identity(d,d);

		--ite;
		for (j = 0; j < d-1; ++j){
			for (i = j+1; i < d; ++i){
				Pij = EigenProblem::montagemQR(A, i, j); //aqquiuiui
				A = Pij*A;
				// QT = Pij.transpose()*QT;
				QT = Pij * QT;
				// Q = Pij * Q;
				// Q = Q * Pij;
			}
		}
		// cout<<"dsa";
		Q = QT.transpose();
		A = A*Q;
		eigenVectorMatrix = eigenVectorMatrix*Q;
		// cout << endl<< A<<endl;
	}
	eigenValues = A.diagonal();
	sortEValues();
}