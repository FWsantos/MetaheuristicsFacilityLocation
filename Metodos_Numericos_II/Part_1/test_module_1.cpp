#include "IntegralProblem.cpp"
#include <iostream>

using std::cout;
using std::endl;



void testeCotesLegendre(){

	Funcao *f = new EX();
	double a = 1, b = 3;
	double newtonOpen[4][4];
	double newtonClose[4][4];
	double gaussLegend[4][4];

	for(int j = 0; j < 4; j++)
		for(int i = 0; i < 4; i++){
		 	newtonOpen[j][i] = IntegralProblem().newtonCotesOpen(i+1, f, a, b, j+1);
		 	newtonClose[j][i] = IntegralProblem().newtonCotesClose(i+1, f, a, b, j+1);
		 	gaussLegend[j][i] = IntegralProblem().gaussLegendre(i+1, f, a, b, j+1);
		}

	for(int j = 0; j < 4; j++){
		cout << "Para "<< j+1<<" particoes" <<endl;
		for(int i = 0; i < 4; i++){
			cout << "Para polinomio de grau "<<i+1<<endl;
			cout <<"Newton Aberto   = "<<newtonOpen[j][i]<<endl;
			cout <<"Newton Fechado  = "<<newtonClose[j][i]<<endl;
			cout <<"Gauss  Legendre = "<<gaussLegend[j][i]<<endl;
		}
	}
}

void testeHermiteLaguerreChebyshev(){
	Funcao *f = new Cos();

	for(int i = 2; i <= 4; i++){
		cout <<"para "<< i<< " pontos"<<endl;
	 	// cout<< "Gauss Hermite "<<IntegralProblem().gaussHermite(i, f)<<endl;
	 	// cout<< "Gauss Laguerre "<<IntegralProblem().gaussLaguerre(i, f)<<endl;
	 	cout<< "Gauss Chebyshev "<<IntegralProblem().gaussChebyshev(i, f)<<endl;
	}

}
int main()
{
	testeCotesLegendre();
	// testeHermiteLaguerreChebyshev();

	return 0;
}