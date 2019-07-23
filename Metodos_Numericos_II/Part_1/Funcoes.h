#include <math.h>
class Funcao{
public:
	virtual double valor(double x) = 0;
	// double valor(double *x) = 0;
	// double *valor(double x) = NULL;
	// double *valor(double x) = NULL;
};

class Cos: public Funcao {public:double valor(double x);};

class Sen: public Funcao {public:double valor(double x);};

class X2: public Funcao {public:double valor(double x);};

class EX: public Funcao {public:double valor(double x);};