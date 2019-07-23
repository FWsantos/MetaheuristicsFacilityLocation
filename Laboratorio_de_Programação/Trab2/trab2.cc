#include <cstdlib>
#include <ctime>
#include "instancias_Reais_Trabalho_2.hpp"
#include "metodos.cpp"
// #include <iostream>
// using namespace std;

char *aleatorio(int textsize, int l, char *txt){
	const char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    txt = (char *)malloc((textsize+1) * sizeof(char));
    
    std::srand(std::time(0));
    int aux;
    for (int i = 0; i < textsize; ++i){
    	aux = std::rand() % (l);
    	txt[i] = alfabeto[aux];
    }
    txt[textsize] = '\0';
    

    return txt;
}

int main(int argc, char const *argv[])
{
	int opcao, textsize, padraosize, l;
	char aux;
	char *texto;
	char *padrao;
	int *saida1;
	int *saida2;

	// int saida1[30];

	// forca_bruta("texto","t",saida1);

	// for (int i = 0; saida1[i] != -1; ++i)
	// {
	// 	cout << saida1[i];
	// }
	// cout <<endl;


	
	do{
		// system("clear");
		// system("cls");
		cout<<"1 - Intancia Aleatoria"<<endl;
		cout<<"2 - Pior Caso 1"<<endl;
		cout<<"3 - Pior Caso 2"<<endl;
		cout<<"4 - Textos Reais"<<endl;
		cout<<"5 - Sair"<<endl;
		cout << "opcao> ";
		cin >> opcao;
		if(opcao == 1){
			cout << "insira o tamanho do texto> ";
			cin >> textsize;
			
			do{
				cout << "insira o termo l> ";
				cin >> l;
				if(l <1 || l >26){
					cout << "Erro valor invalido.\n";
					cout << "l precisa esta entre 1 e 26.\n";
				}
			}while(l<1 || l > 26);

			texto = aleatorio(textsize, l, texto);
			do{
				cout << "insira o tamanho do padrao> ";
				cin >> padraosize;
				if (padraosize > textsize){
					cout << "Erro valor invalido.\n";
					cout << "padrao precisa ser menor ou igual ao texto.\n";
				}
			}while(padraosize > textsize);

			padrao = aleatorio(padraosize, l, padrao);
		}else if(opcao == 2){
			cout << "insira o tamanho do texto> ";
			cin >> textsize;
			texto = (char *)malloc((textsize+1) * sizeof(char));
			
			for (int i = 0; i < textsize; ++i){
				texto[i] = 'a';
				// cout << texto[i];
			}
			texto[textsize] = '\0';
			do{
				cout << "insira o tamanho do padrao> ";
				cin >> padraosize;
				if (padraosize > textsize){
					cout << "Erro valor invalido.\n";
					cout << "padrao precisa ser menor ou igual ao texto.\n";
				}
			}while(padraosize > textsize);

			padrao = (char *)malloc((padraosize+1) * sizeof(char));
			for (int i = 0; i < padraosize-1; ++i){
				padrao[i] = 'a';
				// cout << padrao[i];
			}
			padrao[padraosize-1] = 'b';

			padrao[padraosize] = '\0';
		}else if(opcao == 3){
			cout << "insira o tamanho do texto> ";
			cin >> textsize;
			texto = (char *)malloc((textsize+1) * sizeof(char));
			
			for (int i = 0; i < textsize; ++i){
				texto[i] = 'a';
				// cout << texto[i];
			}
			texto[textsize]= '\0';

			do{
				cout << "insira o tamanho do padrao> ";
				cin >> padraosize;
				if (padraosize > textsize){
					cout << "Erro valor invalido.\n";
					cout << "padrao precisa ser menor ou igual ao texto.\n";
				}
			}while(padraosize > textsize);

			padrao = (char *)malloc((padraosize+1) * sizeof(char));
			for (int i = 0; i < padraosize; ++i){
				padrao[i] = 'a';
				// cout << padrao[i];
			}
			padrao[padraosize] =  '\0';
		}else if(opcao == 4){
			texto = Texto_Livros;
			int i;
			cout << "\nInsira um valor entre 1 e 35130 >> ";
			cin>>i;
			i = i-1;
			padrao = Padroes_Palavras[i];

		}else if(opcao == 5){
			cout << endl << "Bye!" << endl;
			break;
		}

	

		for (int i = 0; i < textsize; ++i)
		{
			cout << texto[i];
		}
		cout<<endl;
		for (int i = 0; i < padraosize; ++i)
		{
			cout << padrao[i];
		}
		cout<<endl;



		saida1 = (int *)malloc((textsize+1)*sizeof(int));
		saida2 = (int *)malloc((textsize+1)*sizeof(int));

		clock_t Tempo[2][2];

		Tempo[0][0] = clock();
		forca_bruta(texto, padrao, saida1);
		Tempo[0][1] = clock();
		Tempo[1][0] = clock();
		KMP(texto, padrao, saida2, textsize, padraosize);
		Tempo[1][1] = clock();
		cout << "Forca Bruta\tKMP\n";
		cout << "Tempo\n";
		cout<<(Tempo[0][1]-Tempo[0][0])* 1000.0 / CLOCKS_PER_SEC<<"\t\t";
		cout<<(Tempo[1][1]-Tempo[1][0])* 1000.0 / CLOCKS_PER_SEC<<"\n";
		if(saida1[0] == -1 || saida2[0] == -1){
			cout << "Padrao nao encontrado no texto."<<endl;
		}
		for (int i = 0; saida1[i] != -1; ++i){
			// cout << "algo";
			cout << endl<<saida1[i]<<"\t\t"<<saida2[i];
			if (saida2[i] != saida1[i])
			{
				cout << "erro na saida = "<<i<<endl;
				break;
			}
		}
		cout << endl;
		// cout << endl;
	}while(opcao != 5);

	return 0;
}