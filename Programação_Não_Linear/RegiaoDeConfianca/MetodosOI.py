from Repositorio import *
from Busca import Busca
import numpy as np

class MetodosOI:
	# Metodo do Gradiente para otimização Irrestrita
	def gradiente(self, x, phi, opcao_busca, intervalo, iteracoes):
		k = 0
		t = 0
		dx = phi.gradiente_forward(x, phi.dimensao*[0.01])
		
		while not self.gradiente_eh_nulo(dx) and iteracoes >= k:
			d = self.menos_gradiente(dx)
			if opcao_busca == "exata":
				t = Busca().exata(intervalo, .001, phi)
			else:
				t = Busca().inexata(x, d, 0.5, 0.4, phi)

			for i in range(len(x)):
				x[i] = x[i] + t * d[i]

			k = k + 1
		return x
			
	
	def gradiente_eh_nulo(self, dx):
		for i in range(len(dx)):
			if abs(dx[i]) > 0.01:
				return False
		return True

	def menos_gradiente(self, dx):
		d = []
		for i in range(len(dx)):
			d.append(-1*dx[i])
		return d
def gradient_descent(x0, func):
	#precisão da solução
	precision = 0.001
	#Learning rate: muito pequeno pode demorar muito a convergir; muito grande pode fazer um 'overshoot' ao mínimo
	learning_rate = 0.0001
	#Temos de dar um limite ao número de iteracções
	max_iter = 10000
	x_new = x0
	res = []
	for i in range(max_iter):
		x_old = x_new
		grad = func.gradiente_forward(x_old, func.dimensao*[0.0001])
		#Vamos usar B = 1
		for i in range(func.dimensao):
			x_new[i] = x_old[i] - learning_rate * grad[i]
		f_x_new = func.value(x_new)
		f_x_old = func.value(x_old)
		res = [x_new, f_x_new]
		if(abs (f_x_new - f_x_old) < precision):
			print("Precisão %f alcançada:" % (f_x_new - f_x_old))
			return res
	print("Iteracção máxima alcançada")
	return res
def testada():
	print("Testada")
# x = MetodosOI().gradiente([3,2], F1(2), "exata", 10, 100)
# res = gradient_descent([1,1], F1(2))
# print(res)