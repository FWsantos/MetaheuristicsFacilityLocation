from FLSol import FLSol
from random import randint

class HC:
    def Run(self, fls):
        melhora = True
        best_av = fls.avaliacao()
        while(melhora):
            melhora = False
            for local in range(fls.N):
                for cliente in range(fls.M):
                    if local != fls.local_do_cliente[cliente]:
                        local_old = fls.local_do_cliente[cliente]
                        if fls.VP_move(cliente, local):
                            if fls.move(cliente, local):
                                avi = fls.avaliacao()
                                best_av = avi
                                melhora = True
                                break
                            
                if melhora: # sai do loop em clientes
                    break
        return fls