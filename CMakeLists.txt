cmake_minimum_required(VERSION 3.21)
project(blaspp_ex)

set(CMAKE_CXX_STANDARD 14)

if(ENABLE_CUDA)
    add_compile_definitions(WITH_CUDA)
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)
    set(BLASPP_DIR "/home/vikramg/DFT-FE-softwares/blaspp/gpu")
else()
    set(BLASPP_DIR "/home/vikramg/DFT-FE-softwares/blaspp/cpu")
endif()

add_executable(blaspp_ex main.cpp)
target_include_directories(blaspp_ex PUBLIC ${BLASPP_DIR}/include)
target_link_directories(blaspp_ex PUBLIC ${BLASPP_DIR}/lib64)
if(ENABLE_CUDA)
    set_target_properties(blaspp_ex PROPERTIES
            CUDA_STANDARD 14
            CUDA_STANDARD_REQUIRED ON)
    target_link_libraries(blaspp_ex blaspp CUDA::cublas CUDA::cudart)
endif()