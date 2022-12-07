def impl(a,b):
    return not(a) or b

def bi_impl(a,b):
    return impl(a,b) and impl(b,a)

def permutations(n):
    q = [(True,),(False,)]
    if n==1: 
        return q
    while q:
        index = q[0]
        if len(index) == n:
            break
        else:
            index = q.pop(0)
            q.append(index + (True,))
            q.append(index + (False,))
    return q

class F1:
    def count(self):
        return 2
    def expression(self):
        return "~(p v q) <=> ~p ^ ~q"
    def function(self, *args):
        return bi_impl(not(args[0] or args[1]), not(args[0]) and not(args[1]))
    def is_tautology(self, n):
        for each in permutations(n):
            if(self.function(*each) == False):
                return False
        return True

#Main
f1 = F1()
print(f1.expression())
print(f1.is_tautology(f1.count()))