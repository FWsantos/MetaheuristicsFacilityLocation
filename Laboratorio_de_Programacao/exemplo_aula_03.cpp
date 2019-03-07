#include <iostream>
using std::cin;using std::cout;
#include <new>
using std::nothrow;

double *ler_vetor(int tam)
{
	double *v = new(nothrow) double[tam];
	if(v != nullptr)
	{
		for (int i = 0; i != tam; ++i)
		{
			cout << "Digite v["<<i<<"]: ";
			cin >> v[i];
		}
	}

	return v;
}

double soma(double *v, int tam)
{
	double *fim = v+tam;
	double sum = 0;
	for (double *p = v; p != fim; ++p)
		sum += *p;
	return sum;
}

int main()
{
	int n;
	do{
		cout << "TAM: ";
		cin >> n;
	}while(n < 1);

	double *v = ler_vetor(n);
	
	if (v == nullptr)
	{
		cout << "sem meória!\n";
		return 1;
	}

	double sum = soma(v,n);
	cout << "A soma é "<< sum << '\n';
	delete []v;
}