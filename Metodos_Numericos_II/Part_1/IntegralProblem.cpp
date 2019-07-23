#include "IntegralProblem.h"
	// Newton-Cotes
	// int grau -> grau do polinomio de interpolação
	// int xi -> ponto inicial
	// int xf -> ponto final
	// int m -> numero de partições
double IntegralProblem::newtonCotesOpen(int grau, Funcao* f, double xi, double xf, int m)
{
	// Por algum motivo
	// Alguem não quer nenhuma particao
	if(m < 1)
		return 0.0;
	
	double saida = 0.0, h, a, b, delta = (xf-xi)/m;

	for (int i = 0; i < m; ++i)
	{
		if(i == 0)
			a = xi;
		else
			a = i*delta+xi;
		if(i == m-1)
			b = xf;
		else
			b = (i+1)*delta+xi;

	
		//Chamada de formulas dependendo do grau desejado
		if(grau == 0){
			h = (b-a)/2;
			saida += 2*h*(f->valor(a + h));
		}
		else if(grau == 1){
			
			h = (b-a)/3;

			saida += 3*(h/2)*(f->valor(a + h)+f->valor(a + 2*h));
		}
		else if (grau == 2){

			h = (b-a)/4;

			saida += 4*(h/3)*(2*f->valor(a+h)-f->valor(a+2*h)+2*f->valor(a+3*h));
		}
		else if (grau == 3){

			h = (b-a)/5;

			saida += (5*h/24)*(11*f->valor(a+h)+f->valor(a+2*h)+f->valor(a+3*h)+11*f->valor(a+4*h));
		}
		else if (grau == 4){
			h = (b-a)/6;
			saida += 3*(h/10)*(11*f->valor(a+h)-14*f->valor(a+2*h)+26*f->valor(a+3*h)-14*f->valor(a+4*h)+11*f->valor(a + 5*h));
		}
		else{
			saida += 0;
		}
			// Retorna um erro
	}
	return saida;
}


	// Newton-Cotes
	// int grau -> grau do polinomio de interpolação
	// int xi -> ponto inicial
	// int xf -> ponto final
	// int m -> numero de partições
double IntegralProblem::newtonCotesClose(int grau, Funcao* f, double xi, double xf, int m)
{
	// Por algum motivo
	// Alguem não quer nenhuma particao
	if(m < 1)
		return 0.0;
	
	double saida = 0.0, h, a, b, delta = (xf-xi)/m, aux;

	for (int i = 0; i < m; ++i)
	{
		if(i == 0)
			a = xi;
		else
			a = i*delta+xi;
		if(i == m-1)
			b = xf;
		else
			b = (i+1)*delta+xi;

		//Chamada de formulas dependendo do grau desejado
		if(grau == 1){
			
			h = (b-a);

			saida += (h/2)*(f->valor(a)+f->valor(b));
		}
		else if (grau == 2){

			h = (b-a)/2;
			saida += (h/3)*(f->valor(a)+4*f->valor(a+h)+f->valor(b));
		}
		else if (grau == 3){

			h = (b-a)/3;
			saida += (3*h/8)*(f->valor(a)+3*f->valor(a+h)+3*f->valor(a+2*h)+f->valor(b));
		}
		else if (grau == 4){
			h = (b-a)/4;
			
			// a expressão ficou muito longa
			// por isso separei os termos
			aux = 7*f->valor(a);
			aux += 32*f->valor(a+h);
			aux += 12*f->valor(a+2*h);
			aux += 32*f->valor(a+3*h);
			aux += 7*f->valor(b);
			aux *= 2*(h)/45;
			saida += aux;
		}
		else{
			saida += 0;
		}
			// Retorna um erro
	}
	return saida;
}

// aplica a mudança de variavel necessaria para gauss legendre
double IntegralProblem::mudancaVarGaussLegendre(double a, double b, double xi){
		return ((b-a)/2)*xi + ((a+b)/2);
}

double IntegralProblem::gaussLegendre(int n_pontos, Funcao *f, double xi, double xf, int m){
		// Por algum motivo
	// Alguem não quer nenhuma particao
	if(m < 1)
		return 0.0;
	
	double saida = 0.0, h, a, b, delta = (xf-xi)/m, aux;

	for (int i = 0; i < m; ++i)
	{
		if(i == 0)
			a = xi;
		else
			a = i*delta+xi;
		if(i == m-1)
			b = xf;
		else
			b = (i+1)*delta+xi;

	
		//Chamada de formulas dependendo do numero de n_pontos desejados
		if(n_pontos == 1){
			// vetor w de pesos de legendre
			// vetor roots de raizes de legendre
			double w[] = {2}, roots[] = {0};

			aux = w[0]*f->valor(mudancaVarGaussLegendre(a,b,roots[0]));
			aux *= (b-a)/2;
			saida += aux;
		}
		else if (n_pontos == 2){

			double w[] = {1,1}, roots[] = {0.57735, -0.57735};

			aux = 0;
			for (int j = 0; j < n_pontos; ++j)
				aux += w[j]*f->valor(mudancaVarGaussLegendre(a,b,roots[j]));
			aux *= (b-a)/2;
			saida += aux;
		}
		else if (n_pontos == 3){

			double w[] = {0.888889, 0.555556,0.555556}, roots[] = {0, 0.774597, -0.774597};

			aux = 0;
			for (int j = 0; j < n_pontos; ++j)
				aux += w[j]*f->valor(mudancaVarGaussLegendre(a,b,roots[j]));
			aux *= (b-a)/2;
			saida += aux;
		}
		else if (n_pontos == 4){
		
			double w[] = {0.652145, 0.652145, 0.347855, 0.347855}, roots[] = {0.339981, -0.339981, 0.861136, -0.861136};

			aux = 0;
			for (int j = 0; j < n_pontos; ++j)
				aux += w[j]*f->valor(mudancaVarGaussLegendre(a,b,roots[j]));
			aux *= (b-a)/2;
			saida += aux;

		}
		else if (n_pontos == 5){
		
			double w[] = {0.568889 , 0.478629, 0.478629, 0.236927, 0.236927}, roots[] = {0, 0.538469, -0.538469, 0.90618, -0.90618};

			aux = 0;
			for (int j = 0; j < n_pontos; ++j)
				aux += w[j]*f->valor(mudancaVarGaussLegendre(a,b,roots[j]));
			aux *= (b-a)/2;
			saida += aux;

		}
		else{
			saida += 0;
		}
			// Retorna um erro
	}
	return saida;	
}

double IntegralProblem::gaussHermite(int n_pontos, Funcao *f){
	double saida = 0.0;

	if(n_pontos == 2){
		double roots[] = {0.70710678, -0.70710678}, w[] = {0.88622692, 0.88622692};
		for (int i = 0; i < n_pontos; ++i)
			saida += w[i]*f->valor(roots[i]);
	}
	else if(n_pontos == 3){
		double roots[] = {0, 1.22474487, -1.22474487}, w[] = {1.1816359, 0.29540897, 0.29540897};
		for (int i = 0; i < n_pontos; ++i)
			saida += w[i]*f->valor(roots[i]);
	}
	else if(n_pontos == 4){
		double roots[] = {0.52464762, -0.52464762, 1.65068012, -1.65068012}, w[] = {0.80491409, 0.80491409, 0.08131283, 0.08131283};
		for (int i = 0; i < n_pontos; ++i)
			saida += w[i]*f->valor(roots[i]);
	}
			
	return saida;
}


double IntegralProblem::gaussLaguerre(int n_pontos, Funcao *f){
	double saida = 0.0;

	if(n_pontos == 2){
		double roots[] = {0.58578643, 3.41421356}, w[] = {0.85355339, 0.1464466};
		for (int i = 0; i < n_pontos; ++i)
			saida += w[i]*f->valor(roots[i]);
	}
	else if(n_pontos == 3){
		double roots[] = {0.41577455, 2.24428036, 6.28994508}, w[] = {0.711093, 0.27851973, 0.01038926};
		for (int i = 0; i < n_pontos; ++i)
			saida += w[i]*f->valor(roots[i]);
	}
	else if(n_pontos == 4){
		double roots[] = {0.32254768, 1.7457611, 4.53662029, 9.39507091}, w[] = {0.6031541, 0.35741869, 0.03888791, 0.00053929};
		for (int i = 0; i < n_pontos; ++i)
			saida += w[i]*f->valor(roots[i]);
	}
			
	return saida;
}
// para n pontos de chebshev
double IntegralProblem::gaussChebyshev(int n_pontos, Funcao *f){
	double saida = 0.0, pi = 3.14159265359, xk;
	for (int k = 1; k <= n_pontos; ++k){
		xk = cos(pi*(2*k-1)/(2*n_pontos));
		saida += f->valor(xk);
	}
	saida *= pi/n_pontos;
	return saida;
}

double IntegralProblem::mudancaVarExpSimples(double a, double b, double x){
	return (b-a)/2 + ((a+b)/2)*tanh(x);
}

double IntegralProblem::mudancaVarExpDupla(double a, double b, double x){
	return (b-a)/2 + ((a+b)/2)*tanh((3.14159265359/2)*sinh(x));
}


// m1 = numero de partições da exponenciação
// m2 = numero de partições do newton Cotes
double IntegralProblem::expSimples(int grau, Funcao *f, double xi, double xf, int m1, int m2){
// Por algum motivo
	// Alguem não quer nenhuma particao
	if(m1 < 1)
		return 0.0;
	
	double saida = 0.0, h, a, b, delta = (xf-xi)/m1, M;

	for (int i = 0; i < m1; ++i)
	{
		if(i == 0)
			a = xi;
		else
			a = i*delta+xi;
		if(i == m1-1)
			b = xf;
		else
			b = (i+1)*delta+xi;

		if(abs(a) > abs(b))
			if (a > 0)
				M = 10*a;
			else
				M = -10*a;
		else
			if (b > 0)
				M = 10*b;
			else
				M = -10*b;

		saida += newtonCotesOpen(grau, f, a, b, m2);
	}
	// saida 
	return saida;
}