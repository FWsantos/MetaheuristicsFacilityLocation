#include <iostream>
using namespace std;


void forca_bruta(char* texto, char *padrao, int *saida){
	int k = 0, j = 0;
	for(int i = 0; texto[i] != '\0'; i++){
		// cout << texto[i]<< '\t';
		for(k = 0; padrao[k] != '\0'; k++)
			// if(padrao[k] == texto[i+k])
			// 	cout << padrao[k]<<endl;
			// else
				// break;
			if(padrao[k] != texto[i+k])
				break;

		if (padrao[k] == '\0'){
			saida[j] = i;
			j++;
		}
	}
	saida[j] = -1;
}

void calcular_pi(int* pi, int m, char* padrao){
	
	pi[0] = 0;

	int j = 0, i = 1;

	while(padrao[i] != '\0'){
		if(padrao[i] == padrao[j]){
			j++;
			pi[i] = j;
			i++;
		}else{
			if(j != 0)
				j = pi[j-1];
			else{
				pi[i] = 0;
				i++;
			}
		}
	}
}


void KMP(char* texto, char *padrao, int *saida,int n,int m){
	int pi[m];
	int k =0;

	calcular_pi(pi, m, padrao);

	int padrao_id = 0, texto_id = 0;

	while(texto_id < n){
		if(padrao[padrao_id] == texto[texto_id]){
			padrao_id++;
			texto_id++;
		}
		if(padrao_id == m){
			saida[k] = texto_id - padrao_id;
			k++;
			padrao_id = pi[padrao_id - 1];
		}else if(texto_id < n  && padrao[padrao_id] != texto[texto_id]){
			if(padrao_id != 0)
				padrao_id = pi[padrao_id - 1];
			else
				texto_id++;
		}
	}

	saida[k] = -1;
}
