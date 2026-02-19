program main
    implicit none

    ! объявляем все переменные
    integer :: k, max_iter, i
    real(8) :: e1, e2, d1, d2, tmp
    real(8) :: Xk(2), Xk1(2), Dxk(2)
    real(8) :: Jk(2,2), Fk(2)
    real(8) :: matrix(2,3)

    ! инициализируем начальными данными
    k = 0
    e1 = 1.0d-9
    e2 = 1.0d-9
    max_iter = 1000

    Xk(1) = 1.0d0
    Xk(2) = -1.0d0

    d1 = e1 * 2.0d0
    d2 = e2 * 2.0d0

    print *, "Начальное приближение:", Xk(1), Xk(2)
    print *, "Заданная погрешность: e1 =", e1, " e2 =", e2
    print *, "Предельное число итераций:", max_iter

    do while (d1 > e1 .or. d2 > e2)
        k = k + 1

        if (k > max_iter) then
            print *, "iteration limit error"
            exit
        end if

        ! Получаем Якобиан и невязку
        call get_jacobean(Xk, Jk)
        call get_func_err(Xk, Fk)

        ! Формируем расширенную матрицу J * Dx = -F
        matrix(1,1) = Jk(1,1)
        matrix(1,2) = Jk(1,2)
        matrix(1,3) = -Fk(1)

        matrix(2,1) = Jk(2,1)
        matrix(2,2) = Jk(2,2)
        matrix(2,3) = -Fk(2)

        call solve_slau(matrix, 2, Dxk)

        ! Новое приближение
        Xk1(1) = Xk(1) + Dxk(1)
        Xk1(2) = Xk(2) + Dxk(2)

        ! Пересчитываем коэффициенты
        d1 = 0.0d0
        do i = 1, 2
            if (abs(Fk(i)) > d1) then
                d1 = abs(Fk(i))
            end if
        end do

        d2 = 0.0d0

        if (sqrt(Xk1(1)**2 + Xk1(2)**2) < 1.0d0) then
            do i = 1, 2
                tmp = abs(Xk1(i) - Xk(i))
                if (tmp > d2) d2 = tmp
            end do
        else
            do i = 1, 2
                tmp = abs((Xk1(i) - Xk(i)) / Xk1(i))
                if (tmp > d2) d2 = tmp
            end do
        end if

        ! переходим к новому приближению
        Xk = Xk1

        print *, "Итерация", k, ": d1 =", d1, " d2 =", d2
        print *, "Приближение:", Xk(1), Xk(2)

    end do

    print *, ""
    print *, "Приближенное решение:"
    print *, Xk(1), Xk(2)




































































































contains

subroutine solve_slau(matrix, n, answer)
    implicit none
    integer, intent(in) :: n
    real(8), intent(inout) :: matrix(n, n+1)
    real(8), intent(out) :: answer(n)

    integer :: row, i, j, max_row_index
    real(8) :: max_el, mnozh, temp, total

    do row = 1, n-1
        max_row_index = row
        max_el = 0.0d0

        do i = row, n
            if (abs(matrix(i, row)) > abs(max_el)) then
                max_el = matrix(i, row)
                max_row_index = i
            end if
        end do

        if (row /= max_row_index) then
            do j = 1, n+1
                temp = matrix(row, j)
                matrix(row, j) = matrix(max_row_index, j)
                matrix(max_row_index, j) = temp
            end do
        end if

        do i = row+1, n
            mnozh = matrix(i, row) / matrix(row, row)
            do j = row, n+1
                matrix(i, j) = matrix(i, j) - mnozh * matrix(row, j)
            end do
            matrix(i, row) = 0.0d0
        end do
    end do

    answer = 0.0d0

    do i = n, 1, -1
        total = 0.0d0
        do j = i+1, n
            total = total + answer(j) * matrix(i, j)
        end do
        answer(i) = (matrix(i, n+1) - total) / matrix(i, i)
    end do

end subroutine solve_slau

subroutine get_jacobean(X, result)
    implicit none
    real(8), intent(in) :: X(2)
    real(8), intent(out) :: result(2,2)

    result(1,1) = -sin(0.4d0 * X(2) + X(1)**2) * 2.0d0 * X(1) + 2.0d0 * X(1)
    result(1,2) = -sin(0.4d0 * X(2) + X(1)**2) * 0.4d0 + 2.0d0 * X(2)
    result(2,1) = 3.0d0 * X(1)
    result(2,2) = -X(2) / 0.18d0

end subroutine get_jacobean

subroutine get_func_err(X, result)
    implicit none
    real(8), intent(in) :: X(2)
    real(8), intent(out) :: result(2)

    result(1) = cos(0.4d0 * X(2) + X(1)**2) + X(2)**2 + X(1)**2 - 1.6d0
    result(2) = 1.5d0 * X(1)**2 - (X(2)**2 / 0.36d0) - 1.0d0

end subroutine get_func_err

end program main
