from math import *
import matplotlib
import matplotlib.pyplot as plt
from scipy.stats import t
from scipy.stats import chi2, norm

matplotlib.use('Qt5Agg')

# выборка
X = []

# читаем файл
with open('sample_3.csv', 'r') as file:
    for line in file:
        X.append(float(line.strip()))

# сотритуем массив
X.sort()

# выводим сырой график
ranges1 = []
plt.plot([i for i in range(0, len(X))], X)
plt.xlabel('кол-во меньших значений')
plt.ylabel('значения выборки')
plt.show()

# выводим гистограмму
counts, bins, patches = plt.hist([X], bins=15, color='skyblue', edgecolor='black')
plt.xlabel('интервалы значений выборки')
plt.ylabel('Кол-во значений из интервала в выборке')
plt.show()

# выводим полигон
bin_centers = (bins[:-1] + bins[1:]) / 2
plt.fill(bin_centers, counts, color='skyblue')
plt.xlabel('интервалы значений выборки')
plt.ylabel('Кол-во значений из интервала в выборке')
plt.show()

# выводим эмпирическую функцию распределения
plt.plot(X, [i / len(X) for i in range(1, len(X) + 1)])
plt.xlabel('значения выборки')
plt.ylabel('ЭФР')
plt.show()

# считаем эмпирические моменты
A1 = sum([i**1 for i in X])/len(X)
print('мат. ожидание: '                     + str(A1))

M2 = sum([(i - A1)**2 for i in X])/len(X)
M3 = sum([(i - A1)**3 for i in X])/len(X)
M4 = sum([(i - A1)**4 for i in X])/len(X)
print('дисперсия: '                         + str(M2))
print('стандартное отклонение: '            + str(sqrt(M2)))
print('асимметрия: '                        + str(M3/sqrt(M2)**3))
print('эксцесс: '                           + str(M4/sqrt(M2)**4 - 3))


def g(x):
    return 1/(sqrt(2*3.14)*sqrt(M2)*exp((((x-A1)/sqrt(M2))**2)/2))

# выводим модельную функцию
plt.fill(X, (
    [g(x) for x in X]
), color='skyblue')
plt.show()

# доверительные интервалы
a = 1 - 0.95
A1min = A1 - t.ppf(1 - a/2, len(X))*sqrt(M2/len(X));
A1max = A1 + t.ppf(1 - a/2, len(X))*sqrt(M2/len(X));
M2min = (len(X)-1)*M2/chi2.ppf(1 - a/2, len(X) - 1);
M2max = (len(X)-1)*M2/chi2.ppf(a/2, len(X) - 1);

print('Дов. интервал мат. ожидания: ['  + str(round(A1min, 5)) + '; ' + str(round(A1max, 5)) + ']')
print('Дов. интервал дисперсии: ['      + str(round(M2min, 5)) + '; ' + str(round(M2max, 5)) + ']')

# критерий пирсона
countsG = []
for i in range(0, len(counts)):
    countsG.append(len(X) * (norm.cdf((bins[i+1]-A1)/sqrt(M2))-norm.cdf((bins[i]-A1)/sqrt(M2))))
chiE = sum([((counts[i]-countsG[i])**2)/countsG[i] for i in range(0, len(counts))])
chiK = chi2.ppf(1-a, len(counts) - 3)

print('Хи квадрат эмп.: '   + str(chiE))
print('Хи квадрат крит.: '  + str(chiK))
print('Выполняется критерий пирсона: ' + ('да' if chiE <= chiK else 'нет'))










