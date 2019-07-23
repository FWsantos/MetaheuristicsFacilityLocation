from FL import FL
from FL import generate_instances
from FLSol import FLSol
from HC import HC
from RMS import RMS
from VND import VND
from ILS import ILS
from VNS import VNS
from SA import SA
from GLS import GLS
from AG import AG
from GRASP import GRASP
import copy as cp
import time


problemas = []

problemas.append(generate_instances('instances/Holmberg_Instances/', 2))
problemas.append(generate_instances('instances/OR-Library_Instances/', 1))


k = 0
for problema in problemas:
    for i in problema:
        s = []
        inicial_r = FLSol(i)
        if(inicial_r.M > 100):
            continue
        print(i.nome)
        print("N:",inicial_r.N," M:",inicial_r.M)
        
        hc  = HC()
        vnd = VND()
        rms = RMS()
        ils = ILS()
        vns = VNS()
        sa  = SA()
        gls  = GLS()
        ag  = AG()
        grasp = GRASP()

        # Ponto inicial guloso
        inicial_g = FLSol(i)
        tempo = time.perf_counter()
        inicial_g.build_greedy()
        sb = cp.deepcopy(inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["PTG",sb.avaliacao(), tempo])

        # # Ponto inicial Randomico
        tempo = time.perf_counter()
        inicial_r.build_random()
        tempo = time.perf_counter() - tempo
        sb = cp.deepcopy(inicial_r)
        s.append(["PTR",sb.avaliacao(), tempo])
        
        # HIll CLIMB
        sb = cp.deepcopy(inicial_g)
        tempo = time.perf_counter()
        sb = hc.Run(sb)
        tempo = time.perf_counter() - tempo
        s.append(["HC",sb.avaliacao(), tempo])
        
        # Variable Neighborhood Descendent
        sb = cp.deepcopy(inicial_g)
        tempo = time.perf_counter()
        sb = vnd.Run(inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["VND",sb.avaliacao(), tempo])

        # RANDOM MULT START
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = rms.Run(int(sb.M*sb.N*0.01), inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["RMS", sb.avaliacao(), tempo])

        # # Iterated Local Search
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = ils.Run(int(sb.M*sb.N*0.009), inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["ILS", sb.avaliacao(), tempo])

        # # Variable Neighborhood Search
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = vns.Run(int(sb.M*sb.N*0.005), int(sb.N*sb.N),inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["VNS", sb.avaliacao(), tempo])

        # Gado Local Search
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = gls.Run(50, inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["GLS", sb.avaliacao(), tempo])        

        # Greedy Random Adptative Search Procedure (GRASP)
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = grasp.Run(20, inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["GRASP", sb.avaliacao(), tempo])        


        # # Simulated Annealing
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = sa.Run(int(sb.M*sb.N), inicial_g)
        tempo = time.perf_counter() - tempo
        s.append(["SA", sb.avaliacao(), tempo])


        # Algoritmo Genetico
        tempo = time.perf_counter()
        sb = cp.deepcopy(inicial_g)
        sb = ag.Run(150, inicial_g, 40)
        tempo = time.perf_counter() - tempo
        s.append(["AG", sb.avaliacao(), tempo])

        for x in range(len(s)):
            print("{0:>5}".format(s[x][0]),"{0:>18.5f}".format(s[x][1]),"{0:>11.5f}s".format(s[x][2]))
    #     break
    # break