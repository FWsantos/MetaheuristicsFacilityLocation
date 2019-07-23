#include "avl.hpp"
#include <cstdlib>

// Inicializa D como uma  ́arvore vazia.
void inicializar (DicAVL &D){
	D.raiz == NULL;
}

// Retorna um ponteiro para o novo// n ́o, ou nulo se erro de aloca ̧c~ao
Noh* inserir (DicAVL &D, TC c, TV v){
	if(D.raiz == NULL){
		try{

			D.raiz = (Noh *)malloc(sizeof(Noh));;
		}catch(int x){
			return NULL;
		}

		D.raiz->chave = c;
		D.raiz->valor = v;

		D.raiz->esq = NULL;
		D.raiz->dir = NULL;
		D.raiz->pai = NULL;
		D.raiz->h = 0;
	
	}else{
		Noh* aux = D.raiz;
		Noh* pai = D.raiz;
		int k = 0;
		while(aux != NULL){
			pai = aux;
			k++;
			if(c > aux->chave)
				aux = aux->dir;
			else
				aux = aux->esq;
		}

		aux = (Noh *)malloc(sizeof(Noh));
		aux->chave = c;
		aux->valor = v;

		aux->esq = NULL;
		aux->dir = NULL;
		aux->pai = pai;
		aux->h = k;

		return aux;
	}
}

// Retorna um ponteiro para o n ́o da// chave procurada, ou nulo se a chave// n~ao estiver em D.
Noh* procurar (DicAVL &D, TC c){
	Noh* aux = D.raiz;
	while(aux != NULL){
		
	}
}
// void remover (DicAVL &D, Noh *n);
// // ’n’ aponta para o n ́o a ser removido
// void terminar (DicAVL &D);
// // Desaloca os n ́os da  ́arvore.