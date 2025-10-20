gfortran main.f90 $(pkg-config --cflags --libs plplot-fortran) -lX11
./a.out
