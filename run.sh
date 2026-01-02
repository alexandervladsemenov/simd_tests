echo "C++ with no SIMD exponent"
build/testBilateral_cpp_no_simd 10000 5 0.5;
echo "\nC++ with SIMD exponent\n"
build/testBilateral_cpp 10000 5 0.5;
echo "\nFortran\n"
build/testBilateral_fortran 10000 5 0.5
echo "\nRust\n"
build/testBilateral_rust 10000 5 0.5
