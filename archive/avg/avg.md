# Problema da Árvore Geradora Mínima

## Algoritmos

- Prim
- Kruskal

Ambos $O(nlogn)$

## Algoritmo de Prim

- Iniciamos uma árvore $S$ com um vértice $v_0$ arbitrário
- Recursivamente escolhemos a aresta de menor peso que ligue $S$ à $V - S$ e adicionamos à $S$
- Fazemos isso até que $S$ possua todos os vértices de $V$

Obs.: Não necessariamente a árvore geradora mínima é única

### Pseudo-código

```js
Prim (G=(V,E), w[]):
  x = {}
  S = {v_0}

  while len(S) != len(V) - 1:
    Escolha e em E de menor peso entre S e V-S
    X = X U {e}
    S = S U {extremo de e em V-S}
  
  return X
```

```js
Prim (G, w, v_0):
  for v in V:
    custo[v] = Inf
    prev[v] = -1

  custo[v_0] = 0

  M = Fila_prioridade_min(v, custo)

  while (!M.empty()):
    v = M.pop() // retorna e remove de M

    for u in N(v):
      if custo[u] > w(v, u):
        custo[u] = w(v, u)
        H.decrease_priority(u , custo[u])
        prev[u] = v 
```