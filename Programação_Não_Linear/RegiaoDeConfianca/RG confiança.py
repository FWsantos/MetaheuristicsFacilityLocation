import numpy as np
import simpy as sp
import matplotlib.pyplot as plt #biblioteca de gráficos

def f_x(x):
    return np.power(x,2) +36*x

def grad_f_x(x):
    return 2*x + 36

# Aplicação do método Região de Confiança com busca exata seção aúrea
# O subproblema foi resolvido atráves do passo de Cauchy
x=[]
d=[]
t=[]
delta=[]
ared=[]
pred=[]
p=[]
m=[]
m2=[]
k = 0
w=0
x.insert(0,float(input('Defina x[0] um ponto inicial ')))
delta.insert(0,float(input('Defina delta[0]>0 o raio da região de confiança ')))
e = float(input('Defina a precisão do intervalo busca exata seção aúrea'))
L = float(input('Defina  o alcance do intervalo'))
n=0
while n<0 or n > 1/4:
    n = float(input('Defina uma quantidade n ,tal que 0 < n < 1/4'))
    if n<0 or n > 1/4:
        print('coloque um valor valido para n , positivo e menor que 1/4')
theta1 = (3-np.sqrt(5))/2
theta2 = 1 - theta1
# Fase 1 - Obtenção do intervalo [a,b]
a = 0
s = L
b = 2*L
while grad_f_x(x[k])!=0:
    #  obtendo d_k , por solução aproximada do subproblema
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
    d.insert(k, ((-1)*(t[k])*(grad_f_x(x[k]))))
#     calculando p_k usanod redução entre  razão real e predita
#     no termo 1/2*d[k] transposto vezes B[k]d a matriz B aproximada foi omitida pois tomamso como I por enquanto
    m.insert(k,( (f_x(x[k])) - (grad_f_x(x[k])*d[k] + (1/2)*d[k] ) )  )
    m2.insert(k, ((f_x(d[k])) - (grad_f_x(d[k]) * d[k] + (1 / 2) * d[k])))
    ared = (f_x(x[k]) - f_x(x[k]+d[k]))
    pred = (m[0] - m2[k])
    p.insert(k,(ared/pred) )
    if p[k]>n:
        x.insert( k+1, x[k]+d[k] )
    elif p[k]<n:
        x.insert(k+1, x[k]+ d[k])
    elif p[k]<1/4:
        delta.insert(k+1, delta[k]/2)
    else:
        for w in range(0,k):
            norm = np.sqrt(sum((d[w]) ** 2))
        if p[k]>3/4 and norm == delta[k]:
            delta.insert(k+1, 2*delta[k])
        else:
            delta.insert(k+1, delta[k])
    k=k+1
print('Cabo')
print(f'valor final da função objetivo é :{f_x(x[k])}')



