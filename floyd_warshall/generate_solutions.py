import os
import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import floyd_warshall

INF = float('inf')

# Função para ler o arquivo e criar a CSR matrix
def ler_matriz_adjacencia_arquivo(arquivo):
    with open(arquivo, "r") as f:
        # Ler número de vértices na primeira linha
        n = int(f.readline().strip())
        
        # Ler as linhas restantes para formar a matriz
        matriz = []
        for _ in range(n):
            linha = list(map(int, f.readline().strip().split()))
            matriz.append(linha)
        
        # Converter para numpy array
        matriz = np.array(matriz)
        
        # Substituir -1 por 0 (indicando ausência de aresta)
        matriz[matriz == -1] = 0
        
        # Criar a CSR matrix
        csr = csr_matrix(matriz)
        return csr

instances_path = "./instances"
solutions_path = "./solutions"

for instance in os.listdir(instances_path):
    arquivo = os.path.join(instances_path, instance)

    csr = ler_matriz_adjacencia_arquivo(arquivo)

    with open(os.path.join(solutions_path, instance), "w") as f:
        dist_matrix = floyd_warshall(csgraph=csr, directed=True)

        for row in dist_matrix:
            for num in row:
                if (num == INF):
                    print("INF", end=" ", file=f)
                else:
                    print(int(num), end=" ", file=f)
            print(file=f) 