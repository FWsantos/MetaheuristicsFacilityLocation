#include <iostream>
using std::cin;using std::cout;
#include <new>
using std::nothrow;

double *ler_vetor(int tam)
{
	double *v = new(nothrow) double[tam];
	for (int i = 0; i != tam; ++i)
	{
		if(v == nullptr)
			dobrar_vetor(v);

		cout << "Digite v["<<i<<"]: ";
		cin >> v[i];
	{

	return v;
}

void dobrar_vetor(double *v, int tam)
{       
	double *t = new(nothrow) double[2*tam];
	for (int i = 0; i != tam; ++i)
		*t = *(v+i);
	
	
}

int main(){
    int tam = 5;
    double *v = *ler_vetor(tam);
    cout << *v;
    for(int i = 0; i != tam; ++i)
        cout << ", "<<*(v+i);

    return 0;
}
