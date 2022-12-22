from pylab import *

def s_func(x, a, b, y):
    if x <= a:
        return 0
    if a < x <= b:
        return 2*pow(((x-a)/(y-a)), 2)
    if b < x < y:
        return 1 - 2*pow(((x-y)/(y-a)), 2)
    return 1

def z_func(x, a, b, y):
    if x <= a:
        return 1
    if a < x <= b:
        return 1 - 2*pow(((x-a)/(y-a)), 2)
    if b < x < y:
        return 2 * pow(((y - x) / (y - a)), 2)
    else:
        return 0

def pi_func(x, b, y):
    if x == y:
        return 1
    if x <= y:
        return s_func(x, y - b, y-b*0.5, y)
    if x > y:
        return z_func(x, y, y+b*0.5, y+b)

x = list(list())
y = list(list())
edges = [0, 20, 60, 70, 80, 100]
'''for i in range(0, 150):
    s_answ = s_func(i, 70, 75, 100)
    if not(s_answ < 0):
        if(len(y) == 0):
            x.append(i)
            y.append(s_answ)
        elif not(s_answ < y[-1]):
            x.append(i)
            y.append(s_answ)'''

for i in range(0, 150):
    s_answ = z_func(i, 10, 20, 30)
    x.append(list())
    y.append(list())
    x[0].append(i)
    y[0].append(s_answ)

    s_answ = pi_func(i, 20, 40)
    x.append(list())
    y.append(list())
    x[1].append(i)
    y[1].append(s_answ)

    s_answ = pi_func(i, 20, 60)
    x.append(list())
    y.append(list())
    x[2].append(i)
    y[2].append(s_answ)

    s_answ = s_func(i, 80, 90, 100)
    x.append(list())
    y.append(list())
    x[3].append(i)
    y[3].append(s_answ)



figure()
for i in range(len(x)):
    plot(x[i], y[i], color = 'blue')
xlabel('x')
ylabel('y')
title('Графики')
show()
