program main
    implicit none

    ! переменные для обработки матрицы и тд
    integer :: n, i, j, k, row, max_row_index
    real(16) :: max_el, mnozh, sum

    ! переменные для текущей матрицы
    real(16), allocatable :: matrix(:,:)
    real(16), allocatable :: orig_matrix(:,:)
    real(16), allocatable :: temp_row(:)
    real(16), allocatable :: answer(:)
    real(16), allocatable :: residual(:)

    ! читаем файл
    open(unit=0, file="/home/ilyakrn/CLionProjects/LabsNGTU/fortran/nodes.txt", status='old', action='read')
    do
        ! читаем размер слау
        read(0, *) n
        if (n == -1) then
            exit
        end if

        ! выделяем память на матрицу и ответ
        allocate(matrix(n, n+1))
        allocate(orig_matrix(n, n+1))
        allocate(answer(n))
        allocate(temp_row(n+1))
        allocate(residual(n))

        ! читаем матрицу
        do i = 1, n
            read(0, *) matrix(i, 1:n+1)
        end do

        ! сохраняем слау для вычисления вектора невязки
        orig_matrix = matrix

        print *, "============================"
        print *, "Исходная СЛАУ:"
        call print_slau(n, matrix)

        ! приводим к верхне треугольному виду с выбором главного элемента по столбцу
        do row = 1, n
            ! значение максимального элемента и индекс его строки
            max_el = 0
            max_row_index = row

            ! поиск максимального элемента в столбце
            do i = row, n
                if (abs(matrix(i, row)) > abs(max_el)) then
                    max_el = matrix(i, row)
                    max_row_index = i
                end if
            end do

            ! обмен строк
            if (max_row_index /= row) then
                do k = 1, n+1
                    temp_row(k) = matrix(row, k)
                end do
                do k = 1, n+1
                    matrix(row, k) = matrix(max_row_index, k)
                end do
                do k = 1, n+1
                    matrix(max_row_index, k) = temp_row(k)
                end do
            end if

            ! обнуление столбца
            do i = row+1, n
                mnozh = matrix(i, row) / matrix(row, row)
                do j = row, n+1
                    matrix(i, j) = matrix(i, j) - mnozh * matrix(row, j)
                end do
            end do
        end do

        ! выводим преобразованную слау
        print *, "Преобразованная СЛАУ:"
        call print_slau(n, matrix)

        ! считаем ответ
        do i = n, 1, -1
            sum = 0
            do j = i+1, n
                sum = sum + answer(j) * matrix(i, j)
            end do
            answer(i) = (matrix(i, n+1) - sum) / matrix(i, i)
        end do

        ! выводим ответ
        print *, "Ответ:"
        do i = 1, n
            print *, answer(i)
        end do

        ! считаем вектор невязки
        do i = 1, n
            sum = 0
            do j = 1, n
                sum = sum + orig_matrix(i,j) * answer(j)
            end do
            residual(i) = sum - orig_matrix(i, n+1)
        end do

        print *, "Вектор невязки:"
        do i = 1, n
            print *, residual(i)
        end do
        print *, "============================"

        deallocate(matrix)
        deallocate(answer)
        deallocate(temp_row)
        deallocate(residual)
        deallocate(orig_matrix)
    end do

    ! закрываем файл
    close(0)

contains

    subroutine print_slau(n, a)
        integer, intent(in) :: n
        real(16), intent(in) :: a(n, n+1)
        integer :: i, j
        do i = 1, n
            do j = 1, n
                write(*,'(F12.6)', advance='no') a(i,j)
                write(*,'(A)', advance='no') " "
            end do
            write(*,'(A,F12.6)') "= ", a(i, n+1)
        end do
    end subroutine print_slau

end program main
