from FLSol import FLSol
from HC import HC
from random import randint
import copy as cp


class VND:
    def Run(self, fls):
        melhora = True
        best_av = fls.avaliacao()
        current = cp.deepcopy(fls)

        
        while(melhora):
            # vizinhança 1
            current = HC().Run(current)
            # vizinhança 2
            # Troca dois clientes
            melhora = False
            for cliente1 in range(current.M):
                for cliente2 in range(cliente1):
                    local1 = current.local_do_cliente[cliente1]
                    local2 = current.local_do_cliente[cliente2]

                    # checo se estão em locais diferentes
                    if local1 != local2:
                        # checo se vale a pena troca os clientes
                        if current.VP_move2(cliente1, cliente2):
                            # checo se consigo trocar
                            if current.swap(cliente1, cliente2):
                                # ja troquei, agora salvo o valor dessa avaliacao
                                avi = current.avaliacao()
                                best_av = avi
                                melhora = True
                                # sai do ultimo loop for
                                break
                                
                if melhora: # sai do primeiro loop for
                    break
            # print(melhora)
        return current