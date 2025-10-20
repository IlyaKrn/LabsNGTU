module m_module
    implicit none
contains

    ! процедура для чтения узлов аппроксимации
    subroutine get_nodes(x, y, n)
        implicit none
        real(8), allocatable, intent(inout) :: x(:)
        real(8), allocatable, intent(inout) :: y(:)
        integer, intent(inout) :: n

        ! индекс текущего узла
        integer :: node
        ! открывайм файл, читаем кол-во узлов и выделяем память
        open(unit=0,file='nodes.txt',status='old',action='read')
        read(0, *) n
        allocate(x(n))
        allocate(y(n))
        ! читаем узлы
        do node = 1, n
            read(0, *) x(node)
            read(0, *) y(node)
        end do
        ! закрываем файл
        close(0)
    end subroutine get_nodes

    ! процедура для вычисления коэффициентов полинома
    subroutine get_coeffs(x, y, n, coeffs)
        implicit none
        real(8), allocatable, intent(inout) :: x(:)
        real(8), allocatable, intent(inout) :: y(:)
        integer, intent(inout) :: n
        real(8), intent(inout) :: coeffs(4)

        ! слау для вычисления коэффициентов
        integer :: i, j
        real(8) :: slau(4, 5)
        real(8) :: xDegrees(7)
        real(8) :: right(4)
        real(8) :: mnozh

        ! вычисляем необходимые суммы
        do i = 1, n
            xDegrees(1) = xDegrees(1) + 1
            xDegrees(2) = xDegrees(2) + x(i)
            xDegrees(3) = xDegrees(3) + x(i) * x(i)
            xDegrees(4) = xDegrees(4) + x(i) * x(i) * x(i)
            xDegrees(5) = xDegrees(5) + x(i) * x(i) * x(i) * x(i)
            xDegrees(6) = xDegrees(6) + x(i) * x(i) * x(i) * x(i) * x(i)
            xDegrees(7) = xDegrees(7) + x(i) * x(i) * x(i) * x(i) * x(i) * x(i)

            right(1) = right(1) + y(i)
            right(2) = right(2) + y(i) * x(i)
            right(3) = right(3) + y(i) * x(i) * x(i)
            right(4) = right(4) + y(i) * x(i) * x(i) * x(i)
        end do

        ! составляем слау
        do i = 1, 4
            do j = 1, 4
                slau(i, j) = xDegrees(i + j - 1)
            end do
            slau(i, 5) = right(i)
        end do

        ! зануляем столбцы
        do i = 2, 4
            mnozh = slau(i, 1) / slau(1, 1)
            do j = 1, 5
                slau(i, j) = slau(i, j) - mnozh * slau(1, j)
            end do
        end do
        do i = 3, 4
            mnozh = slau(i, 2) / slau(2, 2)
            do j = 2, 5
                slau(i, j) = slau(i, j) - mnozh * slau(2, j)
            end do
        end do
        do i = 4, 4
            mnozh = slau(i, 3) / slau(3, 3)
            do j = 3, 5
                slau(i, j) = slau(i, j) - mnozh * slau(3, j)
            end do
        end do

        ! считаем ответ
        coeffs(4) = (slau(4, 5)) / slau(4, 4)
        coeffs(3) = (slau(3, 5) - coeffs(4) * slau(3, 4)) / slau(3, 3)
        coeffs(2) = (slau(2, 5) - coeffs(4) * slau(2, 4) - coeffs(3) * slau(2, 3)) / slau(2, 2)
        coeffs(1) = (slau(1, 5) - coeffs(4) * slau(1, 4) - coeffs(3) * slau(1, 3) - coeffs(2) * slau(1, 2)) / slau(1, 1)

    end subroutine get_coeffs

end module m_module


program main
    use m_module
    use plplot
    implicit none

    ! узлы аппроксимации и коэфициенты
    integer :: n
    real(8), allocatable :: x(:)
    real(8), allocatable :: y(:)
    real(8) :: coeffs(4)

    ! отрисовка графиков
    integer :: i, j, points_count
    real(8) :: xmin, xmax, ymin, ymax
    real(8), allocatable :: x_func(:), y_func(:)

    ! получаем узлы и коэффициенты
    call get_nodes(x, y, n)
    call get_coeffs(x, y, n, coeffs)

    ! настраиваем параметры отрисовки
    points_count = 1000
    xmin = x(1) - 1
    xmax = x(n) + 1
    ymin = 0
    ymax = 0
    do i= 1, n
        if (ymin > y(i)) then
            ymin = y(i)
        endif
        if (ymax < y(i)) then
            ymax = y(i)
        endif
    end do
    ymin = ymin - 1
    ymax = ymax + 1

    ! вычисляем значения графика
    allocate(x_func(points_count))
    allocate(y_func(points_count))
    do i = 1, points_count
        x_func(i) = xmin + (xmax - xmin) * real(i - 1) / real(points_count - 1)
        y_func(i) = coeffs(1) + coeffs(2) * x_func(i) + coeffs(3) * x_func(i)**2 + coeffs(4) * x_func(i)**3
    end do


    ! открытие окна и отрисовка
    call plinit()
    call plenv(xmin, xmax, ymin, ymax, 0, 0)
    call pllab('x', 'y', '')
    call plline(x_func, y_func)
    call plpoin(x, y, 9)


    ! закрываем программу
    call plend()
    deallocate(x)
    deallocate(y)
    deallocate(x_func)
    deallocate(y_func)

end program main
