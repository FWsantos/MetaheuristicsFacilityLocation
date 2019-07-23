from FLSol import FLSol
from random import randint
import copy as cp
from HC import HC

class GRASP:
	def Run(self, iterations, fls):
		best_av = fls.avaliacao()
		best_sol = cp.deepcopy(fls)
		for i in range(iterations):
			current = cp.deepcopy(fls)
			current = self.greedRandom(fls)
			current = HC().Run(current)
			current_av = current.avaliacao()
			if current_av < best_av:
				best_av = current_av
				best_sol = cp.deepcopy(current)
		return best_sol

	def greedRandom(self, fls):
		# Construção
		for client in range(fls.M):
			local = 0
			# random_client = randint(0,fls.M-1)
			alpha = 0.1
			# location_candidate = min(fls.custo_alocacao[client])
			location_candidate = randint(0,fls.N-1)

			while fls.capacidade[location_candidate] < (fls.alocado_no_local[location_candidate]+fls.demanda[client]):
				location_candidate = randint(0,fls.N-1)
				# print("nada")
			for x in range(int(fls.N*alpha)):
				local = randint(0,fls.N-1)
				
				# min = 9999999999999999
				# min_arg = -1

				# for it in range(1000):
				# 	local = randint(0,fls.N-1)
				# 	if fls.capacidade[local] >= fls.alocado_no_local[local]+fls.demanda[client] and fls.custo_alocacao[local][client] < min:


					
				ite = 0
				while fls.custo_alocacao[local][client] <= fls.custo_alocacao[location_candidate][client] and local == location_candidate  and (fls.capacidade[local] < fls.alocado_no_local[local]+fls.demanda[client]) and (ite < 1000):
					# print("sei", ite)
					local = randint(0,fls.N-1)
					ite += 1
				location_candidate = local

			fls.move(client, location_candidate)
		return fls