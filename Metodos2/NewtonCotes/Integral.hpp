
// Grau -> 1,2,3,...,n
// Funcao -> 1,2,3,...,m
// Funcao -> 1,2 {1:A, 2:F}
class Integral
{
public:

	int gerar_codigo(int grau, bool filosofia, Funcao funcao){
		int codigo = 0;
		if(filosofia)
			codigo = 1;
		else
			codigo = 2;

		codigo*=100;

		codigo+=grau;
		codigo*=10;
		codgo+=funcao.getNum();
	}

	Integral(int a, int b, int grau, bool filosofia, double erro, Funcao funcao){
		double resultado_old = 0;
		double resultado_now = erro;

		while(resultado_now-resultado_old >= erro){
			switch(codigo){
				case 1011:
				
			}
		}

	}
	// integral();
	// ~integral();
	
};