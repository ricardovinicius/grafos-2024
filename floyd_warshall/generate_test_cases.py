import random

INF = float('inf')

def generate_graph(num_vertices, max_weight=10, density=0.5):
    graph = [[INF] * num_vertices for _ in range(num_vertices)]
    
    for i in range(num_vertices):
        graph[i][i] = 0 
        
        for j in range(num_vertices):
            if i != j and random.random() < density:  
                graph[i][j] = random.randint(1, max_weight) 
                
    return graph

num_vertices = random.randint(50, 200)
graph = generate_graph(num_vertices)
print(num_vertices)
for row in graph:
    for num in row:
        if (num == INF):
            print(-1, end=" ")
        else:
            print(num, end=" ")
    print() 
