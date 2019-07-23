import numpy as np
import scipy as scp
import matplotlib.pyplot as plt #biblioteca de gráficos

def f_x(x):
    return np.power(x + 2, 2) - 16 * np.exp(-np.power((x - 2), 2))

def grad_f_x(x):
    return (2 * x - 4) - 16 * (-2 * x + 4) * np.exp(-np.power(x - 2, 2))
x=[]
d=[]
t=[]
x.insert(0,float(input('Defina um ponto inicial')))
k=0
e = float(input('Defina a precisão do intervalo'))
p = float(input('Defina  o alcance do intervalo'))
print(f'A função em x[0] é:{f_x(x[k])}')
print(f'E seu gradiente em x[0] é : {grad_f_x(x[k])} ')

theta1 = (3 - np.sqrt(5)) / 2
theta2 = 1 - theta1
# Fase 1 - Obtenção do intervalo [a,b]
a = 0
s = p
b = 2 * p

while grad_f_x(x[k]) !=0:
    d.insert(k,(-1)*(grad_f_x(x[k])))
    # obtendo tk >0
    # Fase 2 - Obtenção do tamanho do passo [a,b]
    u = a + (theta1 * (b - a))
    v = a + (theta2 * (b - a))
    while f_x(b) < f_x(s):
        a = s
        s = b
        b = 2 * b
    while (b - a) > e:
        if f_x(u) < f_x(v):
            b = v
            v = u
            u = a + (theta1 * (b - a))
        else:
            a = u
            u = v
            v = a + (theta2 * (b - a))
    t.insert(k, (u + v) / 2)
    x.insert(k,x[k] +(t[k]*d[k]))
    print(f'k vale {k}')
    print(f'o tamanho do passo é {t[k]}')
    k=k+1

    print(x[k])
    print(f'\n O valor da função objetivo é: {f_x(x[k])}')
print(f'O valor final da função objetivo é:{f_x(x[k])}')
plt.plot(f_x(x[k]),grad_f_x(x[k]),'ro')
plt.axis((0,p,0,p))
plt.show()


