from FLSol import FLSol
from VND import VND
import copy as cp
from random import randint

# randint(0,fls.M-1)
# fls.local_do_cliente[] vai ser meu cromossomo

class AG:
	def initPop(self, fls, popsize):
		self.populacao = []
		self.popsize = popsize
		self.taxa = int(popsize*0.2)
		for i in range(popsize):
			current = cp.deepcopy(fls)
			current.build_random()
			current = VND().Run(current)

			self.populacao.append(current) # adiciona a populacao inicial
			# for x in range(len(self.populacao)):
			# 	print("ite ",x,self.populacao[x].avaliacao())

	def selecao(self):
		for i in range(self.taxa): #Quantidade de elementos a ser eliminados
			a = 1
			b = a
			while(a == b): #Obter individuos diferentes
				a = randint(0,self.popsize -1) #sorteia um individuo da populacao
				b = randint(0,self.popsize -1) #sorteia um individuo da populacao
			if(self.populacao[a].avaliacao() < self.populacao[b].avaliacao()):
				self.populacao.pop(b)
			else:
				self.populacao.pop(a)

			self.popsize -= 1 # atualizar o tamanho da população
	# cruzamento
	def offspring(self):
		for i in range(self.taxa): #Quantidade de elementos a serem inseridos
			a = 1 #pai
			b = a #mãe
			while(a == b): #Obter individuos diferentes
				# print("ta aqui")
				a = randint(0, self.popsize -1) #sorteia um individuo da populacao
				b = randint(0, self.popsize -1) #sorteia um individuo da populacao
			# print('Sai')
			pai = self.populacao[a]
			mae = self.populacao[b]
			filho = cp.deepcopy(mae)
			posix = randint(0, self.populacao[0].M -1)
			
			for x in range(posix):
				filho.move(x, pai.local_do_cliente[x])

			self.populacao.append(filho)
			self.popsize += 1

	def melhor(self):
		best = self.populacao[0]
		best_av = best.avaliacao()

		for current in self.populacao:
			current_av = current.avaliacao()
			if current_av < best_av:
				best = current
				best_av = current_av
		return best
			
	# geracoes_max = numero maximo de geracoes/criterio de parada
	def Run(self, geracoes_max, fls, popsize):
		# current = cp.deepcopy(fls)
		self.fls = fls
		self.initPop(fls, popsize)

		for x in range(geracoes_max-1):
			self.selecao()
			self.offspring()

		return self.melhor()
		# return fls