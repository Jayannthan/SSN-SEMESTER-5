from binarytree import build

def generate(limit):
    values=[]
    for i in range(1,2**(limit+1)):
        values.append(i)
    print(values)
    return values


def successors(node):
  return 2 * node, 2 * node + 1

def evaluate(node):
  return node


def maxplayer(node,level,limit):
    ans = 0
    for nextNode in successors(node):
      ans = max(ans, minimax(nextNode, 'min', level + 1, limit))
    values[node - 1] = str([node, ans])
    return ans

def minplayer(node,level,limit):
    ans = 10000 
    for nextNode in successors(node):
      ans = min(ans, minimax(nextNode, 'max', level + 1, limit))
    values[node - 1] = str([node, ans])
    return ans

def minimax(node, player, level, limit):
  if level == limit:
    ans = evaluate(node)
    values[node - 1] = str([node, ans])
    return ans
   
  if player == 'max':
    return maxplayer(node,level,limit)
  else:
    return minplayer(node,level,limit)
   


limit = int(input('Enter limit : '))
print("Building Tree")

values = generate(limit)
print(values)
root = build(values)
print(root)

print('Answer : ', minimax(1, 'max', 0, limit))
