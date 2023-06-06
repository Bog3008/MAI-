class MyItems():
    def __init__(self, name, weight, price):
        self._name = name
        self._weight = weight
        self._price = price
    @property
    def name(self):
        return self._name
    @property
    def weight(self):
        return self._weight
    @property
    def price(self):
        return self._price

def viewTable(table, index, capacity):
    sep_len = 10
    print('capacity'.ljust(sep_len), end='|')
    for i in range(capacity + 1):
        print(str(i).ljust(sep_len), end='')
    print()
    print('-' * (capacity + 1)*sep_len)
    for name, row in zip(index, table):
        print(name.ljust(sep_len), end='|')
        for i in row:
            print(str(i).ljust(sep_len), end='')
        print()
def knapsack_max_value(itemsList, capacity):
    weights = [i.weight for i in itemsList]
    values = [i.price for i in itemsList]
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w])
            else:
                dp[i][w] = dp[i - 1][w]
    index_names = ['empty'] + [i.name for i in itemsList]
    selected_items = []
    i, j = n, capacity
    while i > 0 and j > 0:
        if dp[i][j] != dp[i - 1][j]:
            selected_items.append(index_names[i])
            j -= weights[i - 1]
        i -= 1
    viewTable(dp, index_names,capacity)
    print('selected items is:', selected_items)
    return dp[n][capacity]

myCapacity = 4
itemsList = [MyItems('stapler', weight=4, price=3000),
             MyItems('pencil', weight=3, price=2000),
             MyItems('note', weight=1, price=1500),]

max_value = knapsack_max_value(itemsList,  myCapacity)
print("Максимальная стоимость:", max_value)
