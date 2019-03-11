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
	*inicio = particiona(inicio, fim, inicio+tam/2);
	
}