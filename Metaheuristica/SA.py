from FLSol import FLSol
from VND import VND
from math import *
from VNS import VNS
from random import random, randint
import copy as cp

class SA():
	def Run(self, ite, fls):
		current = VND().Run(fls)
		best = cp.deepcopy(current)
		T0 = 1000
		T = T0
		for i in range(ite):
			vizinho = cp.deepcopy(current)
			self.pertub(vizinho)
			delta = vizinho.avaliacao() - current.avaliacao()
			if delta < 0:
				current = cp.deepcopy(vizinho)
				if vizinho.avaliacao() < best.avaliacao():
					best = cp.deepcopy(vizinho)
			else:
				a = random()
				if a < exp((-1*delta)/T):
					current = cp.deepcopy(vizinho)
			T = 0.99*T #Decresce a temperatura em 15% a cada ite. .
			best = cp.deepcopy(current)
		return best

		
	def pertub(self, fls):
		i = 0
		while fls.move(randint(0,fls.M-1),randint(0,fls.N-1)) and i < 1000:# Sorteio um local e um cliente
			i = i +1