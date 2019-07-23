#include "Funcoes.cpp"

class IntegralProblem
{
private:
	// aplica a mudança de variavel necessaria para gauss legendre
	double mudancaVarGaussLegendre(double a, double b, double xi);
	// aplica a mudança de variavel necessaria para exponenciacao simples
	double mudancaVarExpSimples(double a, double b, double x);
	double mudancaVarExpDupla(double a, double b, double x);
public:
	
	// Newton-Cotes
	// int grau -> grau do polinomio de interpolação
	// int xi -> ponto inicial
	// int xf -> ponto final
	// int m -> numero de partições
	double newtonCotesOpen(int grau, Funcao *f, double xi, double xf, int m);
	double newtonCotesClose(int grau, Funcao *f, double xi, double xf, int m);
	// Quadraturas de Gauss
	// n_pontos => número de pontos
	double gaussLegendre(int n_pontos, Funcao *f, double xi, double xf, int m);
	double gaussHermite(int n_pontos, Funcao *f);
	double gaussLaguerre(int n_pontos, Funcao *f);
	double gaussChebyshev(int n_pontos, Funcao *f);	// para n pontos de chebshev

	//Metodos de Exponenciacao
	double expSimples(int grau, Funcao *f, double xi, double xf, int m1, int m2);
	double expDupla(int grau, Funcao *f, double xi, double xf, int m);


};