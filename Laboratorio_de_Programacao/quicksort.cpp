#include <iostream>
using std::cin;using std::cout;
using std::nothrow;using std::endl;
#include <new>

void printVetor(double *v, int tam){
    for (int i = 0; i < tam; ++i)
    {
        cout << "V["<<i<<"] = "<<v[i]<< endl;
        
    }
}
double *ler_vetor(int tam){
    double *v = new(nothrow) double(tam);
    for (int i = 0; i != tam; ++i){
        cout << "Digite v["<<i<<"]: ";
        cin >> v[i];
    }

    return v;
}

void swap(double *a, double *b){
    double aux = *a;
    *a = *b;
    *b = *a;
}

double *particiona(double *inicio, double *fim, double *pivo){
    swap(inicio, pivo);
    double *limite = inicio+1;
    for (double *i = inicio+1; i != fim; ++i)
        if(*i <= *inicio)
            swap(i, limite);
        limite++;           
}

double *quicksort(double *inicio, double *fim, int tam){
    return particiona(inicio, fim, inicio+tam/2);
}

int main(){
    int tam;
    cout << "Tamanho do vetor: ";
    cin >> tam;
    double *v = ler_vetor(tam);
    printVetor(v, tam);
    printVetor(v, tam);
    return 0;
}