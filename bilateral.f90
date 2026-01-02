subroutine str2int(str, int, stat)
    implicit none
    character(len = *), intent(in) :: str
    integer, intent(out) :: int
    integer, intent(out) :: stat

    read(str, *, iostat = stat)  int
end subroutine str2int

subroutine str2real(str, float, stat)
    implicit none
    character(len = *), intent(in) :: str
    real, intent(out) :: float
    integer, intent(out) :: stat

    read(str, *, iostat = stat)  float
end subroutine str2real

program main
    implicit none
    character(len = 256) :: arg_value ! Character variable to store the argument
    integer :: N, count, i, j, status, radius, imax, imin, jmin, jmax, iimax, iimin, jjmin, jjmax
    integer(kind=8) :: total_count
    real, allocatable :: array(:, :), result(:, :), weight(:, :)
    real :: sigma
    real :: start_time, end_time
    count = command_argument_count()
    call RANDOM_SEED()
    radius = 1
    N = 1000
    sigma = 1.0
    do i = 1, count
        call get_command_argument(i, arg_value, status = status)
        if (status == 0) then
            if(i == 1) then
                call str2int(trim(arg_value), N, status)
            end if
            if(i == 2) then
                call str2int(trim(arg_value), radius, status)
            end if
            if(i == 3) then
                call str2real(trim(arg_value), sigma, status)
            end if
            if (status /= 0) then
                print *, "Error parsing argument", i
                STOP 1
            end if
        else
            print *, "Error getting argument", i
            STOP 1
        end if
    end do

    allocate(array(N, N))
    allocate(result(N, N))
    allocate(weight(2 * radius + 1, 2 * radius + 1))
    call RANDOM_NUMBER(array)
    CALL CPU_TIME(start_time)
    total_count = 0
    do i = 1, N
        do j = 1, N
            imin = max(i - radius, 1)
            imax = min(i + radius , N)
            jmin = max(j - radius, 1)
            jmax = min(j + radius , N)
            iimax = radius + imax - i + 1
            iimin = radius + imin - i + 1
            jjmax = radius + jmax - j + 1
            jjmin = radius + jmin - j + 1
            weight(iimin:iimax, jjmin:jjmax) = exp(-(array(imin:imax, jmin:jmax) - array(i, j))**2 / 2 / sigma**2)
            result(i, j) = sum(array(imin:imax, jmin:jmax) * weight(iimin:iimax, jjmin:jjmax))
            result(i, j) = result(i, j) / sum(weight(iimin:iimax, jjmin:jjmax))
            total_count = total_count + (jmax - jmin + 1) * (imax - imin + 1)
        end do
    end do

    CALL CPU_TIME(end_time)
    PRINT *, "CPU Time:", (end_time - start_time) * 1000, "ms"
    print *, "Average", sum(result)/N/N
    print *, "Total Count", total_count
end