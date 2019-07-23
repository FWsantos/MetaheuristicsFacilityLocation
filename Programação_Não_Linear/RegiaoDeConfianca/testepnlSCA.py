# implementação do algoritmo seção aúrea
# busca unidimencional
import numpy as np
import scipy as scp
import matplotlib.pyplot as plt #biblioteca de gráficos
import simpy as sp
from Repositorio import *
def f_x(x):
    return np.power(x + 2, 2) - 16 * np.exp(-np.power((x - 2), 2))


e = float(input('Defina a precisão do intervalo'))
p = int(input('Defina  o alcance do intervalo'))
theta1 = (3-np.sqrt(5))/2
theta2 = 1 - theta1
# Fase 1 - Obtenção do intervalo [a,b]
a = 0
s = p
b = 2*p

def main_plot():
    x = np.arange(a, p, 0.001)
    y = map(lambda u: F4().value(u,u), x)
    plt.plot(x, list(y))
main_plot()
plt.show()

fxx = F4()
while fxx.value(b,b)<fxx.value(s,s):
    a=s
    s=b
    b =2*b
# Fase 2 - Obtenção do tamanho do passo [a,b]
u = a+(theta1*(b-a))
v = a+(theta2*(b-a))
while (b-a)>e:
    if fxx.value(u,u)<fxx.value(v,v):
        b=v
        v=u
        u=a+(theta1*(b-a))
    else:
        a=u
        u=v
        v=a+(theta2*(b-a))
t=(u+v)/2

print(t)
x = np.arange(a, p, 0.001)
y = map(lambda u: fxx.value(u,u), x)
# plt.plot(x, list(y),t)
# plt
plt.show()
