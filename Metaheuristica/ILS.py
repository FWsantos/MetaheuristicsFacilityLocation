from FLSol import FLSol
from VND import VND
import copy as cp
from random import randint


class ILS:
	def Run(self, iteracoes, fls):
		current = cp.deepcopy(fls)
		av_otimo = fls.avaliacao()

		for i in range(iteracoes):
			if(i > 0):
				self.pertub(current) # Gera um novo ponto
			current = VND().Run(current)
			av_current = current.avaliacao() # salva a avaliação deste ponto
			if av_current < av_otimo: # Compara com minha melhor avaliação
				av_otimo = av_current # Atualiza a melhor avaliação
				fls = cp.deepcopy(current) # Atualiza o resultado

		return fls #retorna o resultado

	def pertub(self, fls):
		i = 0
		while fls.move(randint(0,fls.M-1),randint(0,fls.N-1)) and i < 1000:# Sorteio um local e um cliente
			i = i +1