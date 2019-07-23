from FLSol import FLSol
from VND import VND
from HC import HC
import copy as cp
from random import randint

class GLS:
	def Run(self, iteracoes, fls):
		current = cp.deepcopy(fls)
		av_otimo = fls.avaliacao()
		self.penalidade = []
		for i in range(fls.N):
			self.penalidade.append([0]*fls.M)

		for i in range(iteracoes):
			# print("avantes  - ", current.avaliacao())
			# print(current.custo_fixo)
			if(i > 0):
				# Aplica a penalidade
				current.custo_alocacao = self.penault(current)
			# print(current.custo_fixo)
			current = VND().Run(current)
			# current = HC().Run(current)
			# print("avdepois - ", current.avaliacao())
			av_current = current.avaliacao() # salva a avaliação deste ponto
			if av_current < av_otimo: # Compara com minha melhor avaliação
				av_otimo = av_current # Atualiza a melhor avaliação
				fls = cp.deepcopy(current) # Atualiza o resultado
				for l in range(fls.N):
					for k in range(fls.M):		
						fls.custo_alocacao[l][k] -= self.penalidade[l][k]

		# print("av retorno", fls.avaliacao())
		return fls #retorna o resultado


	def penault(self, fls):
		min = fls.alocado_no_local[0]
		# pacote que atende menos
		min_i = 0
		for p in range(fls.N):
			if min > fls.alocado_no_local[p] and fls.qtd_local[p] > 0:
				min = fls.alocado_no_local[p]
				min_i = p
				# print("local ", min_i)

		self.penalidade[min_i] = self.penalidade[min_i]*1.1

		# aplicar penalidade
		fls.custo_fixo[min_i] += self.penalidade[min_i]*fls.custo_fixo[min_i]
		return fls.custo_fixo