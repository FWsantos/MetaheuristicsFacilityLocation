template <typename T>
void swap_i(T* vetor, int a, int b){
	T aux = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = aux;
}