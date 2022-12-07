# Tree Class Definition
class BT:
    def __init__(self, data):
        self.data = data
        self.left = self.right = None


# Generate tree from given array
def gen(array, i, size):
    tree = None
    if i < size:
        tree = BT(array[i])
        tree.left = gen(array, 2*i + 1, size)
        tree.right = gen(array, 2*i + 2, size)
    return tree

# From given info, generate array and build the tree


def genTree(n):
    array = [i for i in range(1, n+1)]
    return gen(array, 0, len(array))

# Print the tree


def printt(tree, level=0):
    if tree == None:
        return
    printt(tree.right, level + 1)
    print(" "*6*level + "==>" + str(tree.data))
    printt(tree.left, level + 1)

# Depth-First Search


def DFS(tree, goal):
    if tree == None:
        return False
    print(tree.data, end=' ')
    if tree.data == goal:
        return True
    return DFS(tree.left, goal) or DFS(tree.right, goal)

# Breadth-First Search


def BFS(tree, goal):
    q = [tree]
    while(q):
        node = q.pop(0)
        if node != None:
            print(node.data, end=' ')
            if node.data == goal:
                return True
            q.append(node.left)
            q.append(node.right)
    return False

# Depth-Limited Search


def DLS(tree, level, goal):
    if tree == None or level < 0:
        return False
    print(tree.data, end=' ')
    if tree.data == goal:
        return True
    return DLS(tree.left, level - 1, goal) or DLS(tree.right, level - 1, goal)

# Iterative Deepening Search


def IDS(tree, level, goal):
    for index in range(level+1):
        print("Level " + str(index) + ":- ")
        DLS(tree, index, goal)
        print()


# Main
n = int(input("Enter no of nos: "))
tree = genTree(n)

print("Tree is:- ")
printt(tree)
print()

goal = int(input("Enter goal: "))
print("DFS is:- ")
DFS(tree, goal)
print()

print("BFS is:- ")
BFS(tree, goal)
print()

level = int(input("Enter level for DLS/IDS: "))
print("DLS with level " + str(level) + " is:- ")
DLS(tree, level, goal)
print()

print("IDS with level " + str(level) + " is:- ")
IDS(tree, level, goal)
print()
