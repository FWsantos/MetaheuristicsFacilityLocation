#include "Utils.hpp"

int main()
{
	FL* fl = gerar_problema("testes1/cap101.txt");
	
	for (int i = 0; i < fl->getN(); ++i){
		cout << "capacidade local "<<i<<" = "<<fl->getCapacidade(i) << endl;
		cout << "Custo fixo local "<<i<<" = "<<fl->getCustoFixo(i) << endl;
		
	}
	return 0;
}
