from FLSol import FLSol
from VND import VND
import copy as cp


class RMS:
	def Run(self, iteracoes, fls):
		current = cp.deepcopy(fls)
		av_otimo = fls.avaliacao()

		for i in range(iteracoes):
			if(i > 0):
				current.build_random() # Gera um novo ponto
			current = VND().Run(current)
			av_current = current.avaliacao() # salva a avaliação deste ponto
			if av_current < av_otimo: # Compara com minha melhor avaliação
				av_otimo = av_current # Atualiza a melhor avaliação
				fls = cp.deepcopy(current) # Atualiza o resultado

		return fls #retorna o resultado