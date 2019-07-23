from random import randint
import glob
import os
# import numpy as np


# passar vetores pra numpy
class FL:
    def __init__(self, N, M, nome):
        self.nome = nome
        self.N = N # Numero de locais
        self.M = M # Numero de clientes
        self.capacidade = [] # Capacidade do local
        self.custo_fixo = [] # Custo fixo em abrir o local
        self.demanda = [] # Demanda do cliente
        self.custo_alocacao = [] # Matriz do custo de alocação de i em j
    
def generate_instance1(caminho):
    file = open(caminho, 'r')
    s_items = file.readlines()
    file.close()
    ite = []
    # ite = s_items.split("\n")
    for x in range(0, len(s_items)):
        a = s_items[x].split(" ")
        for y in range(len(a)):
            if(a[y] != " " and a[y] != "\n" and a[y]):
                ite.append(float(a[y]))

    N = int(ite[0])
    M =int(ite[1])
    fl = FL(N,M, caminho)

    for i in range(0, 2*N, 2):        
        fl.capacidade.append(ite[i+2])
        fl.custo_fixo.append(ite[i+3])
    for i in range(M):
        fl.demanda.append(ite[i+2*N+2])

    for i in range((2 * N) + 2+M, len(ite),M):
        fl.custo_alocacao.append(ite[i:i+M])

    return fl

def generate_instance2(caminho):
    file = open(caminho, 'r')
    s_items = file.readlines()
    file.close()
    ite = []
    for x in range(0, len(s_items)):
        a = s_items[x].split(" ")
        for y in range(len(a)):
            if(a[y] != " " and a[y] != "\n" and a[y] != ''):
                ite.append(float(a[y]))

    N = int(ite[0])
    M = int(ite[1])
    fl = FL(N, M, caminho)
    
    j = 2
    for i in range(fl.N):
        fl.capacidade.append(ite[j])
        fl.custo_fixo.append(ite[j+1])
        j+=2
    for i in range(M):
        fl.demanda.append(ite[j+i])
    for i in range(j+M, len(ite), M):
        fl.custo_alocacao.append(ite[i:i + M])
    

    return fl
    # ler uma pasta
def generate_instances(caminho,tipo):
    fl_v = []
    for arq in os.listdir(caminho):
        if tipo == 1:
            fl_v.append(generate_instance1(caminho+arq))
        if tipo == 2:
            fl_v.append(generate_instance2(caminho+arq))
    return fl_v # retorna um vetor de fl


fl = generate_instance2('instances/Holmberg_Instances/p1')