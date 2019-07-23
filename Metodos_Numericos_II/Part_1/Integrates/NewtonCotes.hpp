#include "../Funcoes.hpp"
#include "Integrates.hpp"
class NewtonCotes: virtual public Integrates{
public:
	double integrar(Funcao *f, int cod, double xi, double xf){
		double h;
		switch(cod){
			/* Explicação do paramero cod
			cod = xy
			x => filosofia
				0 -> fechada
				1 -> aberta
			y => grau do polinomio de interpolacao
				0
				1 -> 1º
				2 -> 2º
				3 -> 3º
				...
			*/
			case 01:
				h = (xf-xi);
				return (h/2)*(f->valor(xi)+f->valor(xf));
			case 02:
				h = (xf-xi)/2;
				return (h/3)*(f->valor(xi)+4*f->valor(xi+h)+f->valor(xf));
			case 03:
				h = (xf-xi)/3;
				return (3*h/8)*(f->valor(xi)+3*f->valor(xi+h)+3*f->valor(xi+2*h)+f->valor(xf));
			case 04:
				h = (xf-xi)/4;
				return (h/90)*(7*f->valor(xi)+32*f->valor(xi+h)+12*f->valor(xi+2*h)+32*f->valor(xi+3*h)+7*f->valor(xf));
			case 10:
				h = (xf-xi)/2;
				return 2*h*(f->valor(xi+h));
			default:
			// retorna flag de erro
				return 123456;
		}
	}
};