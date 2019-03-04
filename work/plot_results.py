import matplotlib.pyplot as plt

filename = 'trace.dat'

x,y = [],[]

with open(filename,'r') as f:
    lines = f.readlines()
    for line in lines:
        value = [float(s) for s in line.split()]
        x.append(value[0])
        y.append(value[1])

print(x)
print(y)

plt.plot(x,y)
plt.show()
