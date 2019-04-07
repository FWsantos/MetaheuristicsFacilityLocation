#include <new>
using std::nothrow;
class FL{
	// numero de facilidades/depositos
	int N;
	// numero de clientes
	int M;
	// capacidades dos N depositos
	double *capacidades;
	// custos fixos nos N depositos
	double *custoFixoDeposito;
	// demanda dos M clientes
	double *demanda;
	//custo de alocação do cliente i com o deposito j
	double **custoAlocacao;

	
public:
	FL(){
		N = 0;
		M = 0;
	}
	FL(int N, int M){
		this->N = N;
		this->M = M;

		capacidades = new(nothrow) double(N);
		custoFixoDeposito = new(nothrow) double(N);
		demanda = new(nothrow) double(M);       
		custoAlocacao = new(nothrow) double *[M];
		for (int i = 0; i < M; ++i)
			custoAlocacao[i] = new(nothrow) double(N);
	}

	int getN(){
		return N;
	}

	int getM(){
		return M;
	}
	void setCapacidade(int k, double valor){
		capacidades[k] = valor;
	}
	double getCapacidade(int k){
		return capacidades[k];
	}
	void setCustoFixo(int k, double valor){
		custoFixoDeposito[k] = valor;
	}
	double getCustoFixo(int k){
		return custoFixoDeposito[k];
	}
	void setDemanda(int k, double valor){
		demanda[k] = valor;
	}
	double getDemanda(int k){
		return demanda[k];
	}
	// ~FL();   
};