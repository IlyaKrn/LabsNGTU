program main
    implicit none

    ! переменные для обработки матрицы и тд
    integer :: n, i, j, k, row, max_row_index
    real(8) :: max_el, mnozh, sum

    ! переменные для текущей матрицы
    real(8), allocatable :: matrix(:,:)
    real(8), allocatable :: temp_row(:)
    real(8), allocatable :: answer(:)

    ! читаем файл
    open(unit=0, file="/home/ilyakrn/CLionProjects/LabsNGTU/nodes.txt", status='old', action='read')
    do
        ! читаем размер слау
        read(0, *) n
        print *, n

        ! выделяем память на матрицу и ответ
        allocate(matrix(n, n+1))
        allocate(answer(n))
        allocate(temp_row(n))

        ! читаем матрицу
        do i = 1, n
            do j = 1, n+1
                read(0, *) matrix(i, j)
            end do
        end do

        ! выводим исходную матрицу
        print *, "============================"
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
                    max_row_index = row
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
            do i = row, n
                mnozh = matrix(i, row) / matrix(row, row)
                do j = row, n+1
                    matrix(i, j) = matrix(i, j) - mnozh * matrix(row, j)
                end do
                !-------------------matrix(i, row) = 0
            end do
        end do

        ! выводим преобразованную слау
        print *, ""
        call print_slau(n, matrix)

        ! считаем ответ
        do i = n, 1, -1
            sum = 0
            do j = 1, n
                sum = sum + answer(j) * matrix(i, j)
            end do
            answer(i) = (matrix(i, n+1) - sum) / matrix(i, i)
        end do

        ! выводим ответ
        print *, ""
        do i = 1, n
            print *, answer(i)
        end do
        print *, ""
        print *, "============================"

        deallocate(matrix)
        deallocate(answer)
    end do

    ! закрываем файл
    close(0)

contains

    subroutine print_slau(n, a)
        integer, intent(in) :: n
        real(8), intent(in) :: a(n, n+1)
        integer :: i, j
        do i = 1, n
            do j = 1, n
                print *, a(i,j)
                print *, " "
            end do
            print *, a(i, n+1)
        end do
    end subroutine print_slau

end program main
