import matplotlib.pyplot as mp
x = []
y = []

# читаем узлы
file1 = open("nodes.txt", "r")
while True:
    line = file1.readline().rstrip()
    if not line:
        break
    x.append(float(line.split(' ')[0]))
    y.append(float(line.split(' ')[1]))
file1.close

# составляем слау
slau = []
xdeg = [0, 0, 0, 0, 0, 0, 0]
ydeg = [0, 0, 0, 0]

for i in range (x.__len__()):
    xdeg[0] += x[i]**0
    xdeg[1] += x[i]**1
    xdeg[2] += x[i]**2
    xdeg[3] += x[i]**3
    xdeg[4] += x[i]**4
    xdeg[5] += x[i]**5
    xdeg[6] += x[i]**6
    ydeg[0] += y[i] * x[i]**0
    ydeg[1] += y[i] * x[i]**1
    ydeg[2] += y[i] * x[i]**2
    ydeg[3] += y[i] * x[i]**3

slau.append([xdeg[0], xdeg[1], xdeg[2], xdeg[3], ydeg[0]])
slau.append([xdeg[1], xdeg[2], xdeg[3], xdeg[4], ydeg[1]])
slau.append([xdeg[2], xdeg[3], xdeg[4], xdeg[5], ydeg[2]])
slau.append([xdeg[3], xdeg[4], xdeg[5], xdeg[6], ydeg[3]])

# зануляем столбцы
for i in range(3):
    mnozh = slau[i+1][0] / slau[0][0]
    for j in range(5):
        slau[i+1][j+0] = slau[i+1][j+0] - mnozh * slau[0][j+0]


for i in range(2):
    mnozh = slau[i+2][1] / slau[1][1]
    for j in range(4):
        slau[i+2][j+1] = slau[i+2][j+1] - mnozh * slau[1][j+1]


for i in range(1):
    mnozh = slau[i+3][2] / slau[2][2]
    for j in range(3):
        slau[i+3][j+2] = slau[i+3][j+2] - mnozh * slau[2][j+2]

# считаем ответ
coeffs = [0, 0, 0, 0]
coeffs[3] = (slau[3][4]) / slau[3][3]
coeffs[2] = (slau[2][4] - coeffs[3] * slau[2][3]) / slau[2][2]
coeffs[1] = (slau[1][4] - coeffs[3] * slau[1][3] - coeffs[2] * slau[1][2]) / slau[1][1]
coeffs[0] = (slau[0][4] - coeffs[3] * slau[0][3] - coeffs[2] * slau[0][2] - coeffs[1] * slau[0][1]) / slau[0][0]

# рисуем график
ox = []
oy = []

for i in range(1000):
    cx = i * (x[0] + abs(x[0] - x[len(x) - 1])) / 1000
    cy = coeffs[0] + coeffs[1] * cx + coeffs[2] * cx**2 + coeffs[3] * cx**3
    ox.append(cx)
    oy.append(cy)

mp.plot(ox, oy)
mp.scatter(x, y)
mp.xlabel('t')
mp.ylabel('C')
mp.show()





