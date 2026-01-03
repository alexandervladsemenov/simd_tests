cmake_minimum_required(VERSION 3.18)
project(testBranch)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
enable_language(Fortran)
set(CMAKE_Fortran_FLAGS_RELEASE  "-O3 -DNDEBUG -ffast-math -march=native ")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -ffast-math -DNDEBUG  -march=native ")
add_executable(testBranch main.cpp)
add_executable(testBilateral_cpp bilateral.cpp)
add_executable(testBilateral_cpp_simd_improved bilateral_cpp_simd_improved.cpp)
add_executable(testBilateral_cpp_no_simd bilateral_no_simd.cpp)
add_executable(testBilateral_fortran bilateral.f90)

# Rust binary
set(RUST_TARGET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rust/target/release)
set(RUST_BINARY_SLOW ${CMAKE_BINARY_DIR}/testBilateral_rust_slow)
set(RUST_BINARY_FAST ${CMAKE_BINARY_DIR}/testBilateral_rust_fast)

add_custom_target(testBilateral_rust ALL
        COMMAND cargo build --bins --release --manifest-path=${CMAKE_CURRENT_SOURCE_DIR}/rust/Cargo.toml
        COMMAND ${CMAKE_COMMAND} -E copy ${RUST_TARGET_DIR}/bilateralRust_fast ${RUST_BINARY_FAST}
        COMMAND ${CMAKE_COMMAND} -E copy ${RUST_TARGET_DIR}/bilateralRust_slow ${RUST_BINARY_SLOW}
        COMMENT "Building Rust benchmark"
        VERBATIM
)