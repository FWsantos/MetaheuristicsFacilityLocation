from math import pow, exp, sin
from abc import ABC, abstractmethod
import copy as cp

class Funcao(ABC):
	def __init__(self,dimensao):
		self.dimensao = dimensao
	def value(self,x):
		pass
	def gradiente_forward(self, x, delta_x):
		dx = []
		for i in range(len(x)):
			x_aux = cp.deepcopy(x)
			x_aux[i] = x_aux[i] + delta_x[i]
			dx.append((self.value(x_aux)-self.value(x))/delta_x[i])
		return dx

class F1(Funcao):
	def value(self, x):
		return pow(x[0],2) + 4*pow(x[1],2) - 4*x[0] - 8*x[1]

class F2(Funcao):
	def value(self, x):
		return (x[0] - pow(x[1],2))*(x[0] - (0.5*pow(x[1],2)))

class F3(Funcao):
	def value(self, x):
		return 2*pow(x[0],3) - 3*pow(x[0],2) - 6*x[0]*x[1]*(x[0] - x[1] - 1)
class F4(Funcao):
	def value(self, x):
		return 0.5*sin(x[0])*sin(x[1]) + 0.5*exp(pow(x[0], 2)+pow(x[1], 2))
class F5(Funcao):
	def value(self, x):
		return 100*pow(x[1] - pow(x[0], 2), 2) + pow(1 - x[0], 2)