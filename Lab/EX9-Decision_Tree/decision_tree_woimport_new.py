import math
from pprint import pprint
deadline = ["Urgent", "Urgent", "Near", "None",
            "None", "None", "Near", "Near", "Near", "Urgent"]
isthereparty = [1, 0, 1, 1, 0, 1, 0, 0, 1, 0]
lazy = [1, 1, 1, 0, 1, 0, 0, 1, 1, 0]
activity = ["Party", "Study", "Party", "Party",
            "Pub", "Party", "Study", "TV", "Party", "Study"]

dataset = [{} for x in range(10)]
for i in range(10):
    dataset[i]["deadline"] = deadline[i]
    dataset[i]["isthereparty"] = isthereparty[i]
    dataset[i]["lazy"] = lazy[i]
    dataset[i]["activity"] = activity[i]


def entropy(dataset):
    values = {}
    for record in dataset:
        if record["activity"] not in values:
            values[record["activity"]] = 0
        values[record["activity"]] += 1
    ans = 0
    for key in values:
        count = values[key]
        probability = values[key] / len(dataset)
        ans -= probability * math.log2(probability)
    return ans


def informationGain(dataset, feature):
    subsets = {}
    for record in dataset:
        if record[feature] not in subsets:
            subsets[record[feature]] = []
        subsets[record[feature]].append(record)

    value1 = entropy(dataset)
    value2 = 0
    for key in subsets:
        subset_entropy = entropy(subsets[key])
        value2 += len(subsets[key]) / len(dataset) * subset_entropy
    return value1 - value2


def dfs(dataset, features, target):
    mySet = set()
    for record in dataset:
        mySet.add(record[target])

    if len(mySet) == 1:
        return dataset[0][target]

    if len(features) == 0:
        return "cant-decide"
    best_feature = -1
    best_information_gain = -1
    for feature in features:
        if informationGain(dataset, feature) > best_information_gain:
            best_information_gain = informationGain(dataset, feature)
            best_feature = feature

    subsets = {}
    for record in dataset:
        if record[best_feature] not in subsets:
            subsets[record[best_feature]] = []
        subsets[record[best_feature]].append(record)

    newFeatures = [x for x in features if x != best_feature]
    ans = {best_feature: {}}
    for key in subsets:
        ans[best_feature][key] = dfs(subsets[key], newFeatures, target)
    return ans


answer = dfs(dataset, ["lazy", "isthereparty", "deadline"], "activity")
pprint(answer)
