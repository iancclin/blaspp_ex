cmake_minimum_required(VERSION 3.21)
project(blaspp_ex)

set(CMAKE_CXX_STANDARD 14)

if(ENABLE_CUDA)
    add_compile_definitions(WITH_CUDA)
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)
    set(SLATE_DIR "/home/vikramg/DFT-FE-softwares/slate/gpu/gcc8.2.0_openmpi4.0.6_nvcc11.4.0")
else()
    set(SLATE_DIR "/home/vikramg/DFT-FE-softwares/slate/cpu/gcc8.2.0_openmpi4.0.6")
endif()

add_executable(blaspp_ex main.cpp)
target_include_directories(blaspp_ex PUBLIC ${SLATE_DIR}/include)
target_link_directories(blaspp_ex PUBLIC ${SLATE_DIR}/lib64)
target_link_libraries(blaspp_ex blaspp)
if(ENABLE_CUDA)
    set_target_properties(blaspp_ex PROPERTIES
            CUDA_STANDARD 14
            CUDA_STANDARD_REQUIRED ON)
    target_link_libraries(blaspp_ex CUDA::cublas CUDA::cudart)
endif()