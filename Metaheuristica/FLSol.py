from FL import FL
from random import randint


class FLSol:
	def __init__(self, fl):
		self.N = fl.N # Numero de locais
		self.M = fl.M # Numero de clientes
		self.capacidade = fl.capacidade # Capacidade do local
		self.custo_fixo = fl.custo_fixo # Custo fixo em abrir o local
		self.demanda = fl.demanda # Demanda do cliente
		self.custo_alocacao = fl.custo_alocacao # Matriz do custo de alocação de i em j
		
		self.local_do_cliente = [] # Local em que o cliente esta alocado
		self.alocado_no_local = [] # Soma das demandas no local
		# self.qtd_local =  np.zeros(N) # Quantidade de clientes no local
		self.qtd_local =  [] # Quantidade de clientes no local
		for i in range(fl.M):
			self.local_do_cliente.append(-1) # Como o cliente ainda não foi alocado então recebe flag -1
		for j in range(fl.N):
			self.alocado_no_local.append(0) # Ninguem ainda foi alocado então o valor é 0
			self.qtd_local.append(0)

			
	# Resetar a solução Corrente
	def reset(self):
		for i in range(self.M):
			self.local_do_cliente[i] = -1 # Como o cliente ainda não foi alocado então recebe flag -1
		for j in range(self.N):
			self.alocado_no_local[j] = 0 # Ninguem ainda foi alocado então o valor é 0
			self.qtd_local[j] = 0

	# Alocar cliente i no local a
	def move(self, i, a):
		if(self.alocado_no_local[a]+self.demanda[i] <= self.capacidade[a]):
			if(self.local_do_cliente[i] != -1): # -1 caso não tenha alocado ele ainda
				self.alocado_no_local[self.local_do_cliente[i]] -= self.demanda[i] # como ele tava alocado então estou tirando ele desse local
				self.qtd_local[self.local_do_cliente[i]] -= 1
			self.alocado_no_local[a] += self.demanda[i]
			self.local_do_cliente[i] = a
			self.qtd_local[a] += 1
			return True
		else:
			return False
			# print("Aviso: Ultrapassa a capacidade")
			# exit() # Lançar uma excessao

	# trocar cliente1 e cliente2

	def swap(self, cliente1, cliente2):
		local1 = self.local_do_cliente[cliente1]
		local2 = self.local_do_cliente[cliente2]

		if(self.alocado_no_local[local1]+self.demanda[cliente2]-self.demanda[cliente1] <= self.capacidade[local1] and self.alocado_no_local[local2]+self.demanda[cliente1]-self.demanda[cliente2] <= self.capacidade[local2]):
			self.alocado_no_local[local1] += self.demanda[cliente2]-self.demanda[cliente1] 				
			self.alocado_no_local[local2] += self.demanda[cliente1]-self.demanda[cliente2] 				

			self.local_do_cliente[cliente1] = local2
			self.local_do_cliente[cliente2] = local1
			return True
		else:
			return False
			# print("Aviso: Ultrapassa a capacidade")
			# exit() # Lançar uma excessao

	# Cria uma solucao inicial, (porem a solução é muito ruim)
	def build_trivial(self):
		for local in range (self.N):
			for cliente in range(self.M):
				if (self.local_do_cliente[cliente] == -1):
					if(self.capacidade[local]-self.alocado_no_local[local]>= self.demanda[cliente]):
						self.alocado_no_local[local] += self.demanda[cliente]
						self.local_do_cliente[cliente] = local
						self.clientes_no_local[local].append(cliente)

	# Cria uma solução aleatoria
	def build_random(self):
		for cliente in range(self.M):
			self.move(cliente,randint(0,self.N-1)) # Sorteio um local para mover o cliente para lá
	
	def build_greedy(self):
		min = 0
		min_i = 0
		min_j = 0
		for x in range(self.M):
			for local in range(self.N):
				for cliente_i in range(self.M):
					if self.local_do_cliente[cliente_i] != -1 and self.capacidade[local] >= self.alocado_no_local[local]+self.demanda[cliente_i]:
						if self.greedy_arg(local, cliente_i) < min:
							min = self.custo_alocacao[local][cliente_i]
							min_i = cliente_i
							min_j = local
			self.move(min_i, min_j)

	def greedy_arg(self, local, cliente):
		k = 1
		# return self.custo_alocacao[local][cliente] + self.custo_fixo[local]*self.demanda[cliente]/(self.capacidade[local]-self.alocado_no_local[local])*k
		return self.custo_alocacao[local][cliente] + self.custo_fixo[local]*(self.capacidade[local]-self.alocado_no_local[local])/self.demanda[cliente]*k

	# Calculo da função de avaliação
	def avaliacao(self):
		total = 0
		for a in range(self.N):
			if self.qtd_local[a] > 0:
				total += self.custo_fixo[a]
		for i in range(self.M):
			total += self.custo_alocacao[self.local_do_cliente[i]][i] #Supor que é NxM(testar pra saber)

		return total

	# Checa se vale a pena mover um cliente para um local
	def VP_move(self, cliente, local):
		local_old = self.local_do_cliente[cliente]
		delta_av = 0 # variacao na troca
		if self.qtd_local[local_old]-1 == 0:
			delta_av -= self.custo_fixo[local_old]
		if self.qtd_local[local] == 0:
			delta_av += self.custo_fixo[local]
		
		delta_av += self.custo_alocacao[local][cliente]-self.custo_alocacao[local_old][cliente]
		if delta_av < 0:
			return True
		return False

	# Checa se vale a pena mover um cliente com cliente
	def VP_move2(self, cliente1, cliente2):
		local1 = self.local_do_cliente[cliente1]
		local2 = self.local_do_cliente[cliente2]

		delta_av = 0 # variacao na troca
		delta_av -= self.custo_alocacao[local1][cliente1]+self.custo_alocacao[local2][cliente2]
		delta_av += self.custo_alocacao[local1][cliente2]+self.custo_alocacao[local2][cliente1]
		if delta_av < 0:
			return True
		return False