#include <iostream>
#include "Teste.hpp"
using namespace std;
int main()
{
    Teste t;
    t.set_values(2,5);
    cout << t.area() << endl;
    
    return 0;
}
