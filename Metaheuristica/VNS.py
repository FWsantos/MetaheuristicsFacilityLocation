from FLSol import FLSol
from VND import VND
from random import randint
import copy as cp


class VNS:
	def Run(self, ite, n, fls):
		best_av = fls.avaliacao()
		current = cp.deepcopy(fls)
		melhorou = True
		n_v = int(fls.N/2)
		# vizinhancas
		# Utilizando VND, encontra um ótimo local
		current = VND().Run(current)
		while melhorou:
			melhorou = False
			# Para todas as n_v vizinhancas
			for v in range(1,n_v+1):
				# Para o numero de iteracoes passadas
				for x in range(n):
					current = cp.deepcopy(fls)
					# De acordo com a vizinhanca aplico as pertubacoes
					for y in range(v):       
						self.pertub(current)
					# Faz a busca local
					current = VND().Run(current)

					av_current = current.avaliacao() # salva a avaliação deste ponto
					if av_current < best_av: # Compara com a melhor avaliação
						best_av = av_current # Atualiza a melhor avaliação
						fls = cp.deepcopy(current) # Atualiza o resultado
						melhorou = True
						break
					
					ite -= 1
					if ite <= 0:
						return fls

				if melhorou:
					break
		return fls
	
	def pertub(self, fls):
		i = 0
		while fls.move(randint(0,fls.M-1),randint(0,fls.N-1)) and i < 1000:# Sorteio um local e um cliente
			i = i +1