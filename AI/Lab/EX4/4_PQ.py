from queue import PriorityQueue

g = {}
node = {}
pos = {}


def create_graph():
    g['A'].append(('B', 9))
    g['B'].append(('A', 9))
    g['A'].append(('C', 6))
    g['C'].append(('A', 6))
    g['B'].append(('D', 5))
    g['D'].append(('B', 5))
    g['C'].append(('D', 8))
    g['D'].append(('C', 8))
    g['D'].append(('E', 7))
    g['E'].append(('D', 7))
    g['C'].append(('F', 5))
    g['F'].append(('C', 5))
    g['D'].append(('G', 6))
    g['G'].append(('D', 6))
    g['H'].append(('E', 4))
    g['E'].append(('H', 4))
    g['G'].append(('F', 7))
    g['F'].append(('G', 7))
    g['H'].append(('G', 8))
    g['G'].append(('H', 8))


def manhattan_dst(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)


def greedy_best_fs(x, y):
    global greedy_path_cost
    f = {}
    visited = set()
    q = PriorityQueue()
    t = node[(x, y)]
    f[t] = manhattan_dst(x, y, 3, 3)
    q.put((f[t], t))
    while q.qsize() > 0:
        (c1, t1) = q.get()
        if t1 in visited:
            continue
        visited.add(t1)
        print((c1, t1))
        greedy_path_cost += 1
        if t1 == 'H':
            break
        for (t, c) in g[t1]:
            (x1, y1) = pos[t]
            f[t] = manhattan_dst(x1, y1, 3, 3)
            q.put((f[t], t))


def a_star(x, y):
    global a_star_path_cost
    f = {}
    visited = set()
    q = PriorityQueue()
    t = node[(x, y)]
    f[t] = manhattan_dst(x, y, 3, 3)
    q.put((f[t], 0, t))
    while q.qsize() > 0:
        (c1, g1, t1) = q.get()
        if t1 in visited:
            continue
        visited.add(t1)
        print((c1, g1, c1 - g1, t1))
        a_star_path_cost += 1
        if t1 == 'H':
            break
        for (t, c2) in g[t1]:
            (x1, y1) = pos[t]
            f[t] = manhattan_dst(x1, y1, 3, 3) + c2 + g1
            q.put((f[t], c2 + g1, t))


c = 'A'
for i in range(1, 4):
    for j in range(1, 4):
        if i == 1 and j == 3:
            continue
        node[(i, j)] = c
        pos[c] = (i, j)
        g[c] = []
        c = chr(ord(c) + 1)

greedy_path_cost = 0
a_star_path_cost = 0

create_graph()
print("\ngreedy best first search\n")
greedy_best_fs(1, 1)
print("\ngreedy path cost: ", greedy_path_cost)

print("\nA* search\n")
a_star(1, 1)
print("\nA* path cost: ", a_star_path_cost)
