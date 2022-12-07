def state(n):
  states = []
  for i in range(1,n+1):
    for j in range(1,n+1):
      states.append((i,j))
  return states

#Main
print("Enter start state")
x = int(input("x: "))
y = int(input("y: "))
start = (x,y)

print("Enter goal state")
x = int(input("x: "))
y = int(input("y: "))
end = (x,y)

n = int(input("Enter no of restricted states: "))
r_states = []
for i in range(0,n):  
  print("Enter restricted state", i+1, ":")
  x = int(input("x: "))
  y = int(input("y: "))
  r_states.append((x,y))