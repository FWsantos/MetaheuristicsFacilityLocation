#include <iostream>
using std::cin;using std::cout;
#include <new>
using std::nothrow;

// QUESTÃO 1
bool sao_iguais (const char *r, const char *s)
{
    for (int i = 0; (*(r+i) != '\0') || (*(s+i) != '\0') ; ++i)
        if(*(r+i) != *(s+i))
            return false;
    return true;
}

// QUESTÃO 2
void inverter (int *v, int n) // Pré-condição: n >= 1   
{
    int aux;
    for (int i = 0; i < n/2; ++i)
    {
        aux = *(v+i);
        *(v+i) = *(v+n-1-i);
        *(v+n-1-i) = aux;

        cout << *(v+i)<<','<<*(v+n-1-i)<<'\n';
    }
}

int main(int argc, char const *argv[])
{
    // Teste para sao_iguais
    char r[] = "blade", s[] = "blade";
    cout  << sao_iguais(r, s) << '\n';  

    // Teste para inverter

    int n = 11;
    int v[n] = {0,1,2,3,4,5,6,7,8,9,10};
    inverter(v, n);
    for (int i = 0; i < n; ++i)
        cout << *(v+i)<<',';
    return 0;
}