# Installation on Greatlakes
1. create a build directory with `mkdir  build`
2. change directory to the build directory `cd /path/to/build`
3. execute `ccmake /path/to/slate/src`
4. press `c` to configure then `t` to toggle to the advanced mode
5. put `-L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread 
   -lm -ldl` in `BLAS_LIBRARIES` blank
6. change `CMAKE_INSTALL_PREFIX` and `prefix` options to the installation directory.
7. execute `make` to build and compile `slate`
8. execute `make install` to install (copy) the headers and the libraries to the installation directory.

## Notes
For GPU/CPU compilation, turn on/off the `gpu_backend` options. Note that the options `use_cuda` and `use_hip` are 
obsoleted.
