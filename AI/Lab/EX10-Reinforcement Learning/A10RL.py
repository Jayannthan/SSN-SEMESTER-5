from pprint import pprint

reward = [
    [-5, 0, 0, 0, 0],
    [0, -5, 0, 0, 0],
    [0, 0, -5, 0, 0],
    [0, 0, 0, -5, 0],
    [0, 0, 0, 0, -5],
]

valid = [
    [0, 0, 1, 1, 0],
    [0, 0, 0, 0, 0],
    [0, 1, 0, 0, 1],
    [0, 1, 1, 0, 0],
    [0, 1, 0, 0, 0],
]
pl = {0: "Canteen", 1: "CSE", 2: "ECE", 3: "Admin", 4: "Auditorium"}


def find_reward(node, l, vst):
    for x in range(5):
        if valid[node][x] > 0:
            if reward[node][x] < pow(5, l):
                reward[node][x] = max(reward[node][x], pow(5, l))
                vst1 = vst + [x]
                find_reward(x, l + 1, vst1)


def find_path(node, vst):
    if node == 1:
        print("Visited:", vst)
        reward_val = 0
        t = 1
        for (x, y) in vst:
            reward_val += y * t
            t *= 0.2
        print("Reward Value:", round(reward_val), "\n")
        return

    for x in range(5):
        if reward[node][x] > 0:
            vst1 = vst + [(x, reward[node][x])]
            find_path(x, vst1)


print("Inital Reward Matrix:")
pprint(reward)
find_reward(0, 1, [0])
print("Final Reward Matrix:")
pprint(reward)
print()

find_path(0, [(0, 0)])
