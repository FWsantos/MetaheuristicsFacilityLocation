#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "FL.hpp"
// #include <sys/types.h>

using namespace std;

FL* gerar_problema(const char *aquivo){
	FILE* fp = fopen(aquivo, "r");
	if(!fp) {
		perror("Falha em abrir o arquivo");
	}
	FL* fl;

	double aux1 = 0;
	double aux2 = 0;
	int N = 0;
	int M = 0;
	int spaces = 0;
	int line = 0;
	bool ponto = false;
	int inNumber = 0;
	
	char c; // note: int, not char, required to handle EOF
	for (int i = 0; (c = fgetc(fp)) != EOF; ++i){
		if(c == ' ' || c == '\n' || c == '.'){
			if(line == 0){
				if(spaces == 1)
					N = aux1;
				if(spaces == 2){
					M = aux1;
					fl = new FL(N,M);
					cout <<"N = "<< fl->getN() << endl;
					cout <<"M = "<< fl->getM() << endl; 
				}
			}else if(line >0 && line <= N){
				if(spaces == 1){
					cout <<"v1 ="<< aux1 << endl;
					fl->setCapacidade(line-1, aux1);
				}
				if(c == '.'){
					cout <<"v2 ="<< aux1 << endl;
					fl->setCustoFixo(line-1, aux1);
				}
			}
			if(c == '\n'){
				line++;
				spaces = 0;
			}else if(c == ' '){
				spaces++;
			}else{
				ponto = true;
				aux2 = 1;               
			}
			aux1 = 0;
			aux2 = 0;
			ponto = false;
		}else{

			if(ponto){
				aux1 += ((int)c - 48)*(0.1*aux2);
				aux2++;
			}else{
				// aux1 *= pow(10, aux2);
				aux1 *= 10;
				aux1 += (int)c - 48;
			}
		}
					// putchar(c);
	}

	if (ferror(fp))
		puts("Erro na Leitura do arquivo");
	else if (feof(fp))
		puts("Arquivo lido com sucesso");


	fclose(fp); 

	return fl;
}

int gerar_problemas(const char *path, FL* fl) {
	struct dirent *entry;
	DIR *dir = opendir(path);

	if (dir == NULL) {
		perror("Diretorio não encontrado");
		return EXIT_FAILURE;
	}

	for (int i = 0; (entry = readdir(dir)) != NULL ; ++i){
		if(i == 2){
			// cout << entry->d_name <<endl;

			char ch[100] = "";
			int k;
			for(k = 0; path[k] != '\0';k++)
				ch[k] = path[k];

			for (int i = 0; *(entry->d_name+i) != '\0' ; ++i)
				ch[k+i] = *(entry->d_name+i);

			cout  << endl;
			for (int i = 0; ch[i] != '\0'; ++i)
				cout << ch[i];
			cout  << endl;


			FILE* fp = fopen(ch, "r");
			if(!fp) {
				perror("Falha em abrir o arquivo");
				return EXIT_FAILURE;
			}

			int aux1 = 0;
			int aux2 = 0;
			int N = 0;
			int M = 0;
			int spaces = 0;
			int line = 0;
			char c; // note: int, not char, required to handle EOF
			for (int i = 0; (c = fgetc(fp)) != EOF; ++i){
				if(c == ' ' || c == '\n'){
					if(line == 0 && spaces == 1)
						N = aux1;
					if(line == 0 && spaces == 2){
						M = aux1;
						// fl = new FL(N,M);
					}
					if(c == '\n')
						line++;
					else
						spaces++;
					aux1 = 0;
					aux2 = 0;
				}else{
					aux1 *= pow(10, aux2);
					aux1 += (int)c - 48;
					aux2++;

				}


				// putchar(c);
			}
			cout <<"N = "<< N << endl;
			cout <<"M = "<< M << endl;

			if (ferror(fp))
				puts("Erro na Leitura do arquivo");
			else if (feof(fp))
				puts("Arquivo lido com sucesso");

			
			fclose(fp);
		}
	}
	closedir(dir);
	return 0;
}