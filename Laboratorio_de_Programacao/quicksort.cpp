#include <iostream>
#include <cstdlib>
#include <ctime>
#include <new>
using namespace std;

// generateDouble()

void printVetor(double *v, int tam){
    for (int i = 0; i < tam; ++i)
    {
        cout << "V["<<i<<"] = "<<v[i]<< endl;
        
    }
}
double *ler_vetor(int tam){
    double *v = new(nothrow) double(tam);
    for (int i = 0; i < tam; ++i){
        cout << "Digite v["<<i<<"]: ";
        cin >> v[i];
    }

    return v;
}

void swap(double *a, double *b){
    double aux = *a;
    *a = *b;
    *b = aux;
}

double *particiona(double *inicio, double *fim, double *pivo){
    // swap(inicio, pivo);
    double *limite = inicio+1;
    for (double *i = inicio+1; i != fim; ++i){
        if(*i <= *inicio){
            swap(i, limite);
            limite++;           
        }
    }
    swap(inicio, limite-1);
    return limite-1;
}

void quicksort(double *inicio, int tam){
    particiona(inicio, inicio+tam, inicio);
}

int main(){
    int tam;
    cout << "Tamanho do vetor: ";
    cin >> tam;
    double *v = ler_vetor(tam);
    printVetor(v, tam);
    particiona(v, v+tam, v);
    cout << endl;
    printVetor(v, tam);
    return 0;
}