import matplotlib.pyplot as plot
import math
def solve_slau(matrix):
    n = len(matrix)

    for row in range(1, n):
        max_row_index = 0
        max_el = 0
        for i in range(row - 1, n):
            if abs(matrix[i][row - 1]) > abs(max_el):
                max_el = matrix[i][row - 1]
                max_row_index = i

        if row - 1 != max_row_index:
            matrix[row - 1], matrix[max_row_index] = matrix[max_row_index], matrix[row - 1]

        for i in range(row, n):
            mnozh = matrix[i][row - 1] / matrix[row - 1][row - 1]
            for j in range(row - 1, n + 1):
                matrix[i][j] -= mnozh * matrix[row - 1][j]
            matrix[i][row - 1] = 0

    answer = [0] * n

    for i in range(n - 1, -1, -1):
        total = 0
        for j in range(n):
            total += answer[j] * matrix[i][j]
        answer[i] = (matrix[i][n] - total) / matrix[i][i]

    return answer


def get_jacobean(X):
    result = [
        [-math.sin(0.4 * X[1] + X[0] * X[0]) * 2 * X[0] + 2 * X[0],
         -math.sin(0.4 * X[1] + X[0] * X[0]) * 0.4 + 2 * X[1]],
        [3 * X[0], -X[1] / 0.18]
    ]
    return result


def get_func_err(X):
    result = [
        math.cos(0.4 * X[1] + X[0] * X[0]) + X[1] * X[1] + X[0] * X[0] - 1.6,
        1.5 * X[0] * X[0] - (X[1] * X[1] / 0.36) - 1
    ]
    return result

def solveSNAU(Xk):
    # начальные данные
    k = 0
    e1 = 1e-9
    e2 = 1e-9
    max_iter = 1000

    # нормы ошибок предыдущей итерации
    d2 = e2 * 2
    d1 = e1 * 2

    # выводим начальные данные
    print(f"Начальное приближение: ({Xk[0]} {Xk[1]})")
    print(f"Заданная погрешность: е1 = {e1}; e2 = {e2}")
    print(f"Предельное число итераций: {max_iter}")

    # начинаем итерации
    while d1 > e1 or d2 > e2:
        k += 1

        # если итераций слишком много, выходим с ошибкой
        if k > max_iter:
            print("iteration limit error")
            break

        # получаем матрицу Якоби и вектор невязки
        Jk = get_jacobean(Xk)
        Fk = get_func_err(Xk)

        # решаем СЛАУ для нахождения дельты
        Dxk = solve_slau([
            [Jk[0][0], Jk[0][1], -Fk[0]],
            [Jk[1][0], Jk[1][1], -Fk[1]],
        ])

        # получаем следующее приближение
        Xk1 = [
            Xk[0] + Dxk[0],
            Xk[1] + Dxk[1],
            ]

        # пересчитываем нормы
        d1 = 0
        d2 = 0
        for i in range(len(Fk)):
            if d1 < abs(Fk[i]):
                d1 = abs(Fk[i])

        if math.sqrt(Xk1[0] * Xk1[0] + Xk1[1] * Xk1[1]) < 1:
            for i in range(len(Fk)):
                tmp = abs(Xk1[i] - Xk[i])
                if d2 < tmp:
                    d2 = tmp
        else:
            for i in range(len(Fk)):
                tmp = abs((Xk1[i] - Xk[i]) / Xk1[i])
                if d2 < tmp:
                    d2 = tmp

        # переходим к новому приближению
        Xk = Xk1

        print(f"Итерация {k}: d1 = {d1}; d2 = {d2}")
        print(f"k-тое приближение: ({Xk[0]} {Xk[1]})")

    print(f"Приближенное решение:\n{Xk[0]}\t\t{Xk[1]}")
    return Xk


def main():

    # получаем значения от приближений
    init1 = [1, -1]
    init2 = [-1, 1]
    ans1 = solveSNAU(init1)
    ans2 = solveSNAU(init2)

    # рисуем график системы и точки приближенного решения
    plot.xlabel("x1")
    plot.ylabel("x2")
    h = 0.02
    a = [-2 + i*h for i in range(int(4/h)+1)]

    X = [[x1 for x1 in a] for _ in a]
    Y = [[x2 for _ in a] for x2 in a]

    Z1 = [[math.cos(0.4*x2 + x1**2) + x2**2 + x1**2 - 1.6
        for x1 in a] for x2 in a]

    Z2 = [[1.5*x1**2 - x2**2/0.36 - 1
        for x1 in a] for x2 in a]


    plot.axhline(0, color='black', linewidth=1)
    plot.axvline(0, color='black', linewidth=1)
    plot.contour(X, Y, Z1, levels=[0])
    plot.contour(X, Y, Z2, levels=[0])
    plot.scatter(ans1[0], ans1[1], color='green')
    plot.scatter(ans2[0], ans2[1], color='green')
    plot.scatter(init1[0], init1[1], color='red')
    plot.scatter(init2[0], init2[1], color='red')

    plot.gca().set_aspect('equal')
    plot.show()

if __name__ == "__main__":
    main()