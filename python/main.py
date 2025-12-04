def print_slau(slau):
    n = slau[0]
    a = slau[1]
    for i in range(n):
        row = "\t".join(str(x) for x in a[i][0:n])
        print(row, "= ", a[i][n])


def get_slaus(filename):
    slaus = []
    with open(filename, "r") as f:
        while True:
            line = f.readline()
            if not line:
                break

            n = int(line.strip())
            matrix = []
            for _ in range(n):
                row = list(map(float, f.readline().split()))
                matrix.append(row)

            slaus.append((n, matrix))

    return slaus


def solve_slau(slau):
    n, a = slau

    # Gaussian elimination with row pivoting
    for row in range(1, n):
        max_el = 0
        max_row_index = row - 1

        for i in range(row - 1, n):
            if abs(a[i][row - 1]) > abs(max_el):
                max_el = a[i][row - 1]
                max_row_index = i

        # swap
        if max_row_index != row - 1:
            a[row - 1], a[max_row_index] = a[max_row_index], a[row - 1]

        # eliminate
        for i in range(row, n):
            mnozh = a[i][row - 1] / a[row - 1][row - 1]
            for j in range(row - 1, n + 1):
                a[i][j] -= mnozh * a[row - 1][j]
            a[i][row - 1] = 0

    return (n, a)


def answer_slau(slau):
    n, a = slau
    ans = [0.0] * n

    for i in range(n - 1, -1, -1):
        s = sum(ans[j] * a[i][j] for j in range(n))
        ans[i] = (a[i][n] - s) / a[i][i]

    return ans


slaus = get_slaus("/home/ilyakrn/CLionProjects/LabsNGTU/nodes.txt")

for slau in slaus:
    n, raw_matrix = slau
    # копии, чтобы не портить исходную
    import copy
    raw_slau = (n, copy.deepcopy(raw_matrix))
    solved = solve_slau((n, copy.deepcopy(raw_matrix)))
    ans = answer_slau(solved)

    print("\n\n============================")
    print_slau(raw_slau)
    print()
    print_slau(solved)
    print()
    print(*ans)
    print("============================\n\n")