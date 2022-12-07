# from binarytree import build
def generate(st,num):
    balls = []
    if(st=="red"):
        for i in range(num):
            balls.append(2*i+1)
    else:
        for i in range(1,num+1):
            balls.append(2*i)
    return balls


def dfs(balls,curr,siz,gs,state):
    if(curr<siz):
        print(balls[curr],end=" ")
        if(balls[curr]==gs):
            return 1
        if(state!=1):
            state=dfs(balls,2*curr+1,siz,gs,state)
            if(state==1):return 1
            state=dfs(balls,2*curr+2,siz,gs,state)
            if(state==1):return 1
        return state
        


def printchild(balls,curr,siz,gs):
    if(2*curr+1<siz):
        print(balls[2*curr+1],end=" ")
        if(balls[2*curr+1]==gs):return 1
    if(2*curr+2<siz):
        print(balls[2*curr+2],end=" ")
        if(balls[2*curr+2]==gs):return 1
    return 0

def bfs(balls,curr,siz,gs,state):
    if(curr<siz):
        state=printchild(balls,curr,siz,gs)
        if(state!=1):
            state=bfs(balls,2*curr+1,siz,gs,state)
        if(state!=1):
            state=bfs(balls,2*curr+2,siz,gs,state)
        return state
        
        


st=str(input("Enter String:"))
num=int(input("Enter number to generate number of balls:"))
print("You have chosen: "+ st)
print("No of balls to generate: " + str(num))

balls=generate(st,num)
print(balls)

# root = build(balls)
# print(root)


gs=int(input("Enter goal state of ball to traverse:"))
print("DFS TRACE:")
dfs(balls,0,num,gs,0)

print()
print("BFS TRACE:\n" + str(balls[0]),end=" ")
f=bfs(balls,0,num,gs,0)
