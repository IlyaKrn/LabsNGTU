program slau_solver
    implicit none

    integer :: n, i, j, row, max_row_index, num_systems
    real(8), allocatable :: a(:,:), answer(:)
    real(8) :: max_el, mnozh, sum
    character(len=256) :: filename
    integer :: io

    filename = "/home/ilyakrn/CLionProjects/LabsNGTU/nodes.txt"

    open(unit=10, file=filename, status='old', action='read')

    do
        read(10, *, iostat=io) n
        if (io /= 0) exit  ! конец файла

        allocate(a(n, n+1))
        allocate(answer(n))

        ! читаем матрицу
        do i = 1, n
            do j = 1, n+1
                read(10, *) a(i, j)
            end do
        end do

        print *, "============================"
        call print_slau(n, a)

        ! --- Гауссово исключение ---
        do row = 2, n
            max_el = 0.0d0
            max_row_index = row - 1

            ! поиск максимального элемента
            do i = row - 1, n
                if (abs(a(i, row - 1)) > abs(max_el)) then
                    max_el = a(i, row - 1)
                    max_row_index = i
                end if
            end do

            ! обмен строк
            if (max_row_index /= row - 1) then
                call swap_rows(a, row - 1, max_row_index, n)
            end if

            ! обнуление столбца ниже диагонали
            do i = row, n
                mnozh = a(i, row - 1) / a(row - 1, row - 1)
                do j = row - 1, n+1
                    a(i, j) = a(i, j) - mnozh * a(row - 1, j)
                end do
                a(i, row - 1) = 0.0d0
            end do
        end do

        print *, ""
        call print_slau(n, a)

        ! --- обратный ход ---
        do i = n, 1, -1
            sum = 0.0d0
            do j = 1, n
                sum = sum + answer(j) * a(i, j)
            end do
            answer(i) = (a(i, n+1) - sum) / a(i, i)
        end do

        print *, ""
        do i = 1, n
            write(*,'(F12.6)', advance='no') answer(i)
        end do
        print *, ""
        print *, "============================"

        deallocate(a)
        deallocate(answer)
    end do

    close(10)

contains

    subroutine print_slau(n, a)
        integer, intent(in) :: n
        real(8), intent(in) :: a(n, n+1)
        integer :: i, j
        do i = 1, n
            do j = 1, n
                write(*,'(F12.6)', advance='no') a(i,j)
                write(*,'(A)', advance='no') " "
            end do
            write(*,'(A,F12.6)') "= ", a(i, n+1)
        end do
    end subroutine print_slau

    subroutine swap_rows(a, r1, r2, n)
        real(8), intent(inout) :: a(:,:)
        integer, intent(in) :: r1, r2, n
        real(8) :: tmp
        integer :: j
        do j = 1, n+1
            tmp = a(r1, j)
            a(r1, j) = a(r2, j)
            a(r2, j) = tmp
        end do
    end subroutine swap_rows

end program slau_solver
