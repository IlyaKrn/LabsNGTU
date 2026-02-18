module slaU
    implicit none
contains

    function solve_slau(matrix) result(answer)
        implicit none
        real(8), intent(inout) :: matrix(:,:)
        real(8), allocatable :: answer(:)
        integer :: n, row, i, j, max_row_index
        real(8) :: max_el, mnozh, total
        real(8), allocatable :: temp_row(:)
        
        n = size(matrix, 1)
        allocate(answer(n))
        allocate(temp_row(n+1))
        
        do row = 2, n
            max_row_index = 1
            max_el = 0.0d0
            
            do i = row-1, n
                if (abs(matrix(i, row-1)) > abs(max_el)) then
                    max_el = matrix(i, row-1)
                    max_row_index = i
                end if
            end do
            
            if (row-1 /= max_row_index) then
                temp_row(:) = matrix(row-1, :)
                matrix(row-1, :) = matrix(max_row_index, :)
                matrix(max_row_index, :) = temp_row(:)
            end if
            
            do i = row, n
                mnozh = matrix(i, row-1) / matrix(row-1, row-1)
                do j = row-1, n+1
                    matrix(i, j) = matrix(i, j) - mnozh * matrix(row-1, j)
                end do
                matrix(i, row-1) = 0.0d0
            end do
        end do
        
        answer = 0.0d0
        
        do i = n, 1, -1
            total = 0.0d0
            do j = 1, n
                total = total + answer(j) * matrix(i, j)
            end do
            answer(i) = (matrix(i, n+1) - total) / matrix(i, i)
        end do
        
        deallocate(temp_row)
        
    end function solve_slau
    
    function get_jacobean(X) result(result_mat)
        implicit none
        real(8), intent(in) :: X(:)
        real(8) :: result_mat(2,2)
        
        result_mat(1,1) = -sin(0.4d0 * X(2) + X(1) * X(1)) * 2.0d0 * X(1) + 2.0d0 * X(1)
        result_mat(1,2) = -sin(0.4d0 * X(2) + X(1) * X(1)) * 0.4d0 + 2.0d0 * X(2)
        result_mat(2,1) = 3.0d0 * X(1)
        result_mat(2,2) = -X(2) / 0.18d0
        
    end function get_jacobean
    
    function get_func_err(X) result(result_vec)
        implicit none
        real(8), intent(in) :: X(:)
        real(8) :: result_vec(2)
        
        result_vec(1) = cos(0.4d0 * X(2) + X(1) * X(1)) + X(2) * X(2) + X(1) * X(1) - 1.6d0
        result_vec(2) = 1.5d0 * X(1) * X(1) - (X(2) * X(2) / 0.36d0) - 1.0d0
        
    end function get_func_err

end module slaU

program main
    use slaU
    implicit none
    
    ! начальные данные
    integer :: k = 1
    real(8) :: e1 = 1.0d-9
    real(8) :: e2 = 1.0d-9
    integer :: max_iter = 1000
    
    ! приближение предыдущей итерации
    real(8) :: Xk(2) = [1.0d0, -1.0d0]
    real(8) :: Xk1(2)
    
    ! нормы ошибок предыдущей итерации
    real(8) :: d2, d1
    real(8) :: Jk(2,2), Fk(2)
    real(8) :: Dxk(2)
    real(8) :: tmp
    integer :: i
    
    d2 = e2 * 2.0d0
    d1 = e1 * 2.0d0
    
    ! выводим начальные данные
    write(*, '(A, F10.6, 1X, F10.6)') "Начальное приближение: (", Xk(1), Xk(2), ")"
    write(*, '(A, E10.3, A, E10.3)') "Заданная погрешность: е1 = ", e1, "; e2 = ", e2
    write(*, '(A, I0)') "Предельное число итераций: ", max_iter
    
    ! начинаем итерации
    do while (d1 > e1 .or. d2 > e2)
        k = k + 1
        
        ! если итераций слишком много, выходим с ошибкой
        if (k > max_iter) then
            write(*,*) "iteration limit error"
            exit
        end if
        
        ! получаем матрицу Якоби и вектор невязки
        Jk = get_jacobean(Xk)
        Fk = get_func_err(Xk)
        
        ! решаем СЛАУ для нахождения дельты
        Dxk = solve_slau(reshape([ &
            Jk(1,1), Jk(2,1), -Fk(1), &
            Jk(1,2), Jk(2,2), -Fk(2)  &
        ], [2, 3]))
        
        ! получаем следующее приближение
        Xk1(1) = Xk(1) + Dxk(1)
        Xk1(2) = Xk(2) + Dxk(2)
        
        ! пересчитываем нормы
        d1 = 0.0d0
        d2 = 0.0d0
        
        do i = 1, size(Fk)
            if (d1 < abs(Fk(i))) then
                d1 = abs(Fk(i))
            end if
        end do
        
        if (sqrt(Xk1(1)*Xk1(1) + Xk1(2)*Xk1(2)) < 1.0d0) then
            do i = 1, size(Fk)
                tmp = abs(Xk1(i) - Xk(i))
                if (d2 < tmp) then
                    d2 = tmp
                end if
            end do
        else
            do i = 1, size(Fk)
                tmp = abs((Xk1(i) - Xk(i)) / Xk1(i))
                if (d2 < tmp) then
                    d2 = tmp
                end if
            end do
        end if
        
        ! переходим к новому приближению
        Xk = Xk1
        
        write(*, '(A, I0, A, E10.3, A, E10.3)') "Итерация ", k, ": d1 = ", d1, "; d2 = ", d2
        write(*, '(A, F10.6, 1X, F10.6)') "k-тое приближение: (", Xk(1), Xk(2), ")"
        
    end do
    
    write(*, '(A, /, F10.6, T30, F10.6)') "Приближенное решение:", Xk(1), Xk(2)
    
end program main