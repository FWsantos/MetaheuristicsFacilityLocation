package Model;

public class Newton_Cotes {
/*
	F -> Funcao a ser integrada
	a -> limite inferior do intervalo a ser integrado
	b -> limite superior do intervalo a ser integrado
	p -> Grau do polinômio de interpolação
	E -> Erro entre as iterações
	opcao -> V = aberto, F = fechada
*/
	public double Calcular(Funcao F, double a, double b, int p, double E, boolean opcao) {
		double N = 1/2, deltaX, XINi, XFINi, I1 = 0, I0 = 0.123456;
		
		for (int ite = 0; ite >=1 && (Math.abs(I0-I1)<= E); ite++) {
			N = 2*N;
			deltaX = (b-a)/N;
			for (int i= 0; i < N; i++) {
				XINi = a+i*deltaX;
				XFINi = XINi+deltaX;

				// Funções Abertas
				if (opcao) {
					// Regra dos Trapezios
					if (p == 1)	{
						I1 = integralAbertaGrau1(F, XINi, XFINi);
					}
					else if (p == 2)	{
						I1 = integralAbertaGrau2(F, XINi, XFINi);
					}
					else if (p == 3)	{
						I1 = integralAbertaGrau3(F, XINi, XFINi);
					}
					else if (p == 4)	{
						I1 = integralAbertaGrau4(F, XINi, XFINi);
					}
				// Funções Fechadas
				}else {
					// Regra dos Trapezios
					if (p == 1)	{
						I1 = integralFechadaGrau1(F, XINi, XFINi);
					}
					else if (p == 2)	{
						I1 = integralFechadaGrau2(F, XINi, XFINi);
					}
					else if (p == 3)	{
						I1 = integralFechadaGrau3(F, XINi, XFINi);
					}
					else if (p == 4)	{
						I1 = integralFechadaGrau4(F, XINi, XFINi);
					}
				}
			}
			
			I0 = I1;
		}
		return I1;
	}

	// Formulas Integrais Abertas
	double integralAbertaGrau1(Funcao F, double a, double b) {
		return 0;
	}
	
	double integralAbertaGrau2(Funcao F, double a, double b) {
		return 0;
	}
	
	double integralAbertaGrau3(Funcao F, double a, double b) {
		return 0;
	}
	
	double integralAbertaGrau4(Funcao F, double a, double b) {
		return 0;
	}
	
	// Formulas Integrais Fechadas
	double integralFechadaGrau1(Funcao F, double a, double b) {
		return (a-b)*(F.valor(a)+F.valor(b))/2;
	}
	
	double integralFechadaGrau2(Funcao F, double a, double b) {
		return 0;
	}
	
	double integralFechadaGrau3(Funcao F, double a, double b) {
		return 0;
	}
	
	double integralFechadaGrau4(Funcao F, double a, double b) {
		return 0;
	}	
	
}
