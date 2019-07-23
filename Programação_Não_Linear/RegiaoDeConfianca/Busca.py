from Repositorio import *
import math

class Busca:
	"""Metodos de busca linear"""

	# Implementação da seção aurea
	def exata(self, p, E, phi):
			# if(p > 0 and E >0):
			# 	exit()

			teta1 = (3-math.sqrt(5))/2
			teta2 = 1-teta1

			# Fase 1: Obtenção do Intervalo [a,b]

			a = 0
			s = p
			b = 2*p
			
			b_aux = []
			s_aux = []
			for i in range(phi.dimensao):
				b_aux.append(b)
				s_aux.append(s)

			while phi.value(b_aux) < phi.value(s_aux):
				a = s
				s = b
				b = 2*b

				b_aux = []
				s_aux = []
				for i in range(phi.dimensao):
					b_aux.append(b)
					s_aux.append(s)

			# Fase 2: Obtenção de t contido em [a,b]

			u = a + teta1*(b-a)
			v = a + teta2*(b-a)

			u_aux = []
			v_aux = []
			for i in range(phi.dimensao):
				u_aux.append(u)
				v_aux.append(v)

			while b-a > E:
				if phi.value(u_aux) < phi.value(v_aux):
					b = v
					v = u
					u = a + teta1*(b-a)
				else:
					a = u
					u = v
					v = a + teta2*(b-a)

				u_aux = []
				v_aux = []
				for i in range(phi.dimensao):
					u_aux.append(u)
					v_aux.append(v)

			# t <= (u+v)/2
			return (u+v)/2

	# Condição de Armijo
	# x pertence a Rn
	# d pertence a Rn (direção de descida)
	# mi, eta pertencem a (0,1) (intervalo aberto)
	def inexata(self, x, d, mi, eta, phi):
		t = 1
		fx = phi.value(x)
		dx = phi.gradiente_forward(x, phi.dimensao*[0.01])

		x_td = len(x)*[0]
		
		const = fx
		for i in range(len(x)):
			x_td[i] = (x[i] + t*d[i])

			const += eta*t*dx[i]+d[i]

		
		fx_td = phi.value(x_td)


		while fx_td+0.001 > const:
					
			t = mi*t

			const = fx
			for i in range(len(x)):
				x_td[i] = (x[i] + t*d[i])

				const += eta*t*dx[i]+d[i]
			
			fx_td = phi.value(x_td)
	
		return t

ine = Busca().inexata([2,2], [1,0], 0.5, 0.2, F1(2))
print(ine)