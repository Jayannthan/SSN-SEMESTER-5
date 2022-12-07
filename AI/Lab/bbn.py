import math

bayesian_network = {"m": ["e", "i"], "s": ["i"], "a": ["m"], "e": [], "i": []}

probability = {"m": [], "s": [], "a": [], "e": [], "i": []}


def input_values():
  for node in bayesian_network:
    print("Enter values for", node)
    length = len(bayesian_network[node])
    values = int(math.pow(2, length))
    for index in range(0, 2*values):
      _input = float(input("[]: "))
      probability[node].append(_input)

def print_values():
  for node in bayesian_network:
    print("Values for", node)
    length = len(bayesian_network[node])
    values = int(math.pow(2, length))
    for index in range(0, values):
      print(probability[node][2*index], probability[node][2*index + 1])

def join_probability():
  result = 1
  for node in bayesian_network:
    length = len(bayesian_network[node])
    values = int(math.pow(2, length+1))
    result *= probability[node][values-1]
  return result

def main():
  print("To represent a bayesian graph for five dependent variables Exam level (e), IQ level(i), apti score(s), marks(m), admission(a)")
  input_values()
  print_values()
  result = join_probability()
  print("The result of the above bayesian graph is: ",result)

# Driver's code
if __name__ == '__main__':
    main()
