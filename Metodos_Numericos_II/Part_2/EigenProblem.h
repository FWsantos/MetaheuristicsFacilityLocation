#ifndef POWER_H
#define POWER_H

#include "Eigen/Dense"
#include "Eigen/LU"
#include <cmath>

#include <iostream>
using namespace Eigen;
using namespace std;


class EigenProblem{
	private:
		VectorXd eigenVector;// autovetor
		double eigenValue;// autovalor
		MatrixXd acumuloH; // Acumulo da matriz de holseholder
		MatrixXd eigenVectorMatrix; // Acumulo da matriz de Jacobi
		VectorXd eigenValues;
		MatrixXd montagemH(MatrixXd A, int i);// Metodo que gera a matriz de holseholder
		double maxMagnitude(VectorXd x);// Retorna o elemento com maior valor absoluto
		MatrixXd montagemJ(MatrixXd A, int i, int j);
		MatrixXd montagemQR(MatrixXd A, int i, int j);
		bool paradaJacobi(MatrixXd A, double E);
		void sortEValues();
		// MatrixXd holseholder(MatrixXd A, int j);// Retorna a matriz de househoder referente a coluna j

	public:
		double getEValue();// Retorna o autovalor
		VectorXd getEVector();// Retorna o autovetor
		MatrixXd getEVectors();
		VectorXd getEValues();
		void regularPower(MatrixXd A, double E, VectorXd x0);// Metodo da potencia regular
		void reversePower(MatrixXd A, double E, VectorXd x0);// Metodo da potencia inversa
		void shiftPower(MatrixXd A, double E, VectorXd x0, double M);// Metodo da potencia com deslocamento
		MatrixXd househoder(MatrixXd A);// Metodo para encontrar matriz tridiagonal
		void jacobi(MatrixXd A, double E, int ite);// Metodo de jacobi
		void QR(MatrixXd A, double E, int ite);// Metodo de QR
};

#endif