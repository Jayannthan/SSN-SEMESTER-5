import math

def printHeuristic(hr):
  ch = 'A'
  for i in range(len(graph)):
    print(chr(ord(ch) + i), end="\t")
  print()
  for i in range(len(hr)):
      print(hr[i],end="\t")

def printGraph(graph):
    print("\t", end="")
    ch = 'A'
    for i in range(len(graph)):
      print(chr(ord(ch) + i), end="\t")
    print()
    for i in range(len(graph)):
      for j in range(len(graph[0])):
        if(j==0 and i==0):
          print("A",end="\t")
        if(j==0 and i==len(graph)-1):
          print("H",end="\t")
        if (j == 0 and i!=0 and i!=len(graph)-1):
            print(chr(ord(ch) + i-1), end="\t")
        print(graph[i][j], end="\t")
      print()

def minDistance(dist,visited,n):
  min=math.inf
  for v in range(n):
    if dist[v] < min and visited[v] == False:
      min = dist[v]
      min_index = v
 
  return min_index

def dijkstra(graph,n,hr):
  dist=[]
  dist1=[]
  visited=[]
  path=[]
  for i in range(n):
    dist.append(math.inf)
    dist1.append(math.inf)
    visited.append(False)
    path.append([])
  start=0
  dist[start]=0
  dist1[start]=0
  path[0].append(0)
  for j in range(n):
    u = minDistance(dist, visited,n)
    visited[u] = True
    for v in range(n):
      if (graph[u][v] > 0 and visited[v] == False and dist[v] > dist[u] +hr[v]):
        dist1[v]=dist1[u] + graph[u][v]
        dist[v] = dist[u] +hr[v]
        for i in range(len(path[v])):
            path[v].pop()
        for i in range(len(path[u])):
            path[v].append(path[u][i])
        path[v].append(v)
  return dist1[n-1],path[n-1]

def astar(graph,n,hr):
  dist=[]
  dist1=[]
  visited=[]
  path=[]
  for i in range(n):
    dist.append(math.inf)
    dist1.append(math.inf)
    visited.append(False)
    path.append([])
  start=0
  dist[start]=0
  dist1[start]=0
  path[0].append(0)
  for j in range(n):
    u = minDistance(dist, visited,n)
    visited[u] = True
    for v in range(n):
      if (graph[u][v] > 0 and visited[v] == False and dist[v] > dist[u] + graph[u][v]+hr[v]):
        dist1[v]=dist1[u] + graph[u][v]
        dist[v] = dist[u] + graph[u][v]+hr[v]
        for i in range(len(path[v])):
            path[v].pop()
        for i in range(len(path[u])):
            path[v].append(path[u][i])
        path[v].append(v)
  return dist1[n-1],path[n-1]
   
# Main Program

graph = [
    [0,9,6,0,0,0,0,0],
    [9,0,0,5,0,0,0,0],
    [6,0,0,8,0,5,0,0],
    [0,5,8,0,7,0,6,0],
    [0,0,0,7,0,0,0,4],
    [0,0,5,0,0,0,7,0],
    [0,0,0,6,0,7,0,8],
    [0,0,0,0,4,0,8,0],
]
hr=[4,3,3,2,1,2,1,0]

n=8
while (True):
  print()
  ch = int(input("Enter choice(1-Print graph, 2-A* search, 3-Greedy):"))
  if (ch == 1):
    print("Graph-")
    print()
    printGraph(graph)
    print()
    print("Heuristic Value-")
    print()
    printHeuristic(hr)
    print()
    print()
  elif(ch==2):
    print("A*")
    v,p=astar(graph,8,hr)
    print("Value = "+ str(v) )
    print("PATH:-")
    ch='A'
    for i in range(len(p)):
      print(chr(ord(ch) + p[i]),end="")
      print(" --> ",end="")
  elif (ch == 3):
    print("Greedy")
    v,p=dijkstra(graph,8,hr)
    print("Value = "+ str(v) )
    print("PATH:-")
    ch='A'
    for i in range(len(p)):
      print(chr(ord(ch) + p[i]),end="")
      print(" --> ",end="")
  else:
      break
