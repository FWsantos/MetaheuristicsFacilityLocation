// #include "Funcoes.hpp"
#include "Integrates.hpp"
#define ERRO 123456;
class GaussLegendre: virtual public Integrates{
public:
	double integrar(Funcao *f, int cod, double xi, double xf){
		double h = (xf-xi)/2;
		switch(cod){
			/* Explicação do paramero cod
			cod = x
			x => numero de pontos
			*/
			case 1:
				return h*(2*f->valor(0));
			case 2:
				return h*(f->valor(1/sqrt(3))+f->valor(-1/sqrt(3)));
			case 3:
				return h*(5/9*f->valor(-sqrt(3/5))+8/9*f->valor(0)+5/9*f->valor(sqrt(3/5)));
			// case 4: // Tô com preguiça, fazer mais tarde
			// 	return h*(5/9*f->valor(-sqrt(3/5))+8/9*f->valor(0)+5/9*f->valor(sqrt(3/5)));
			default:
			// retorna flag de erro
				return ERRO;
		}
	}
};