#include "instancias_ruins_Quicksort.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <new>
using std::nothrow;
using std::cout;using std::endl;using std::cin;

// Gerar vetor com n termos aleatorios de 1 a n
template <typename T>
T* gerar_instancia(int n){
	std::random_device rd;
	std::uniform_int_distribution<T> dist(1,n);
	T *v = new(nothrow) T(n);
	for (T *i = v; i != v+n; ++i)
		*i = dist(rd);
	return v;
}

//swap basico
template <typename T>
void swap(T *a, T *b){
	T aux = *a;
	*a = *b;
	*b = aux;
}


// swap para indices
template <typename T>
void swap_i(T* vetor, int a, int b){
	T aux = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = aux;
}

int escolher_pivo (int primeiro, int ultimo){
	return primeiro;
}

int escolher_pivo_aleatorio(int primeiro, int ultimo){
	srand(time(NULL)); //para gerar números aleatórios reais.
	return rand() % (ultimo - primeiro +1) + primeiro;
}


//Particiona o vetor em 2 partições
template <typename T>
T *particiona(T *inicio, T *fim, T *pivo){
    // swap(inicio, pivo);
	T *limite = inicio+1;
	for (T *i = inicio+1; i != fim; ++i){
		if(*i <= *inicio){
			swap(i, limite);
			limite++;           
		}
	}
	swap(inicio, limite-1);
	return limite-1;

	swap(inicio, limite-1);
	return limite-1;
}

template <typename T>
T* particiona_tri(T *inicio, T *fim, T *pivo){
	swap(inicio, pivo);
	T *limite_1 = inicio+1;
	T retorno[2];
	for (T *i = inicio+1; i != fim; ++i){
		if(*i < *inicio){
			swap(i, limite_1);
			limite_1++;           
		}
	}
	swap(inicio, limite_1-1);
	return retorno;
}

// Particiona usando indices
template <typename T>
int particiona_i(T *vetor, int inicio, int fim, int pivo){
	swap_i(vetor, inicio, pivo);
	int limite = inicio+1;
	for (int i = limite; i < fim; ++i){
		if(vetor[i] < vetor[inicio]){
			swap_i(vetor, i, limite);
			limite++;
		}
	}
	swap_i(vetor, inicio, limite-1);
	return limite-1;
}

template <typename T>
void quicksort_p(T* vetor, int inicio, int fim){
	if(inicio < fim){

		int pivo = escolher_pivo(inicio,fim);
		T *p_pivo = particiona(vetor+inicio, vetor+fim, vetor+pivo);
		pivo = p_pivo-vetor;
		quicksort_p(vetor,inicio, pivo);
		quicksort_p(vetor,pivo+1,fim);
	}
}

template <typename T>
void quicksort_i(T* vetor, int inicio, int fim){
	if(inicio < fim){
		int pivo = escolher_pivo(inicio,fim);
		pivo = particiona_i(vetor, inicio, fim, pivo);
		quicksort_i(vetor, inicio, pivo);
		quicksort_i(vetor, pivo+1, fim);
	}
}

template <typename T>
void quicksort_cauda(T* vetor, int inicio, int fim){
	if(inicio < fim){
		int pivo = escolher_pivo(inicio,fim);
		pivo = particiona_i(vetor, inicio, fim, pivo);
		if(pivo - inicio < fim - pivo){
			quicksort_i(vetor, inicio, pivo);

		}
		quicksort_i(vetor, pivo+1, fim);
	}
}

template <typename T>
void  quicksort_cauda2(T* vetor, int inicio, int fim){
	if(inicio < fim){

		int pivo = escolher_pivo(inicio, fim);
		T*  p_pivo = particiona(vetor+inicio,  vetor+fim, vetor+pivo);

		pivo = p_pivo-vetor;

            // cauda:

		if(pivo - inicio < fim - pivo){
			quicksort_cauda2(vetor, inicio, pivo);

			while(pivo+1 < fim){
				inicio = pivo+1;
				pivo = escolher_pivo(inicio, fim);
				p_pivo = particiona(vetor+inicio,  vetor+fim, vetor+pivo);
				pivo = p_pivo-vetor;
				quicksort_cauda2(vetor, inicio, pivo);
			}
		}else{
			quicksort_cauda2(vetor, pivo+1, fim);                    

			while(pivo > inicio){
				fim = pivo;
				pivo = escolher_pivo(inicio, fim);
				p_pivo = particiona(vetor+inicio,  vetor+fim, vetor+pivo);
				pivo = p_pivo-vetor;
				quicksort_cauda2(vetor, pivo, fim);
			}

		}
	}
}

template <typename T>
int BFPRT(T* v, int a, int b){
	T vetor[b-a];
	int u;
	for (int i = a; i <=b; ++i){
		vetor[i] = v[i];
	}
	int k = 2;
	int j;
	if(b-a < 5){
		quicksort_p(vetor, a, b);
		u = (b-a)/2 + a;
	}else{
		for (j = a; j < b; j += 5){
			k+=5;
			if(b-4 >= j){
				quicksort_p(vetor, j, b);
				swap_i(vetor, a+k, int((b-j)/2)+j);
			}else{
				quicksort_p(vetor, j, j+4);
				swap_i(vetor, a+k, j+2);
			}
		}

		u = (j-a)/5;

		quicksort_p(vetor, a, a+u-1);

		// cout<<"estou aqui "<<j<<endl;
		// int M = a + u/2;
	}
	return a + u/2;
}

template <typename T>
void quicksort_p_BFPRT(T* vetor, int inicio, int fim){
	if(inicio < fim){
		int pivo = BFPRT(vetor, inicio,fim);
		T *p_pivo = particiona(vetor+inicio, vetor+fim, vetor+pivo);
		pivo = p_pivo-vetor;
		quicksort_p_BFPRT(vetor,inicio, pivo);
		quicksort_p_BFPRT(vetor,pivo+1,fim);
	}
}

template <typename T>
void quicksort_p_aleatorio(T* vetor, int inicio, int fim){
	if(inicio < fim){
		int pivo = escolher_pivo_aleatorio(inicio,fim);
		T *p_pivo = particiona(vetor+inicio, vetor+fim, vetor+pivo);
		pivo = p_pivo-vetor;
		quicksort_p_aleatorio(vetor,inicio, pivo);
		quicksort_p_aleatorio(vetor,pivo+1,fim);
	}
}

int checar(int *v, int n){
	for (int i = 1; i < n; ++i)
		if(v[i]< v[i-1])
			return i;
	return -1;
}

void copiar(int *v, int* nv, int n){
	for (int i = 0; i < n; ++i)
	{
		nv[i] = v[i];
	}
}
void quicksort_teste(){
	int n;
	char opcao;
	int* instancia_inicial;
	int* instancia_copia;
	clock_t Tempo[5][2];
	
	cout << endl << "n = ";
	cin >> n;
	
	instancia_inicial = (int *)malloc(n * sizeof(int));
	instancia_copia = (int *)malloc(n * sizeof(int));
	
	cout << endl<< "a = aleatorio";
	cout << endl<< "r = ruim\nopcao >> ";

	cin>>opcao;
	if (opcao == 'a'){
		instancia_inicial = gerar_instancia<int>(n);
	}else{
		bool a = escrever_instancia<int>(instancia_inicial, n);
		cout<<"alalalala";
	}
	// instancia_inicial = gerar_instancia<int>(n);

	cout << endl;

	for (int i = 0; i < 5; ++i)
	{
		int r;

		copiar(instancia_inicial, instancia_copia, n);
		
	
		Tempo[i][0] = clock();
		if(i == 0)
			quicksort_i(instancia_copia, 0, n);
		if(i == 1)
			quicksort_p(instancia_copia, 0, n);
		if(i == 2)
			quicksort_cauda2(instancia_copia, 0, n);
		if(i == 3)
			quicksort_p_BFPRT(instancia_copia, 0, n);
		if(i == 4)
			quicksort_p_aleatorio(instancia_copia, 0, n);

		Tempo[i][1] = clock();

		cout<<"quicksort "<<i+1<<endl;
		cout<<"Tempo = "<<(Tempo[i][1]-Tempo[i][0])* 1000.0 / CLOCKS_PER_SEC<<endl;
		r = checar(instancia_copia, n);
		if( r == -1)
			cout<< "Tudo Ok"<<endl;
		else
			cout<< "Erro no elemento -> "<<r<<endl;
	}

}


int main(int argc, char const *argv[]){
	quicksort_teste();
	return 0;
}