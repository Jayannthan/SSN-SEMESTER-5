from anytree import build
import random


def generate(num, initial, final):
    randnos = []
    randnos = random.sample(range(initial, final+1), num)
    return randnos


def dls(cur_limit, limit, index, arr, N):
    if index >= len(arr):
        return False
    if (limit+1) == cur_limit:
        cur_limit -= 1
        return False
    print(arr[index], end=" ")
    if arr[index] == N:
        return True
    cur_limit += 1
    if dls(cur_limit, limit, 2*index+1, arr, N) == True:
        return True
    if dls(cur_limit, limit, 2*index+2, arr, N) == True:
        return True
    return False


def ids(limit, arr, N):
    for i in range(limit+1):
        print("level " + (str)(i) + ":", end=" ")
        nodes = dls(0, i, 0, randnos, N)
        print()
        if(nodes == True):
            print("\Found " + (str)(limit))
            return
    print("\nNot Found until Level " + (str)(limit))


num = int(input("Enter number to generate number of numbers:"))
intial = int(input("Enter initial number to generate:"))
final = int(input("Enter number to generate number of numbers:"))

randnos = generate(num, intial, final)
print(randnos)

root = build(randnos)
print(root)

N = int(input("Enter goal state : "))
limit = int(input("Enter limit : "))
nodes = dls(0, limit, 0, randnos, N)
# if nodes==False : print("\nNot Found until Level " + (str)(limit))

print()
ids(limit, randnos, N)
