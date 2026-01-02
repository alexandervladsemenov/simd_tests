echo "C++ with no SIMD exponent"
time build/testBilateral_cpp_no_simd 10000 5 0.5;
echo "\nC++ with SIMD exponent"
time build/testBilateral_cpp 10000 5 0.5;
echo "\nFortran"
time build/testBilateral_fortran 10000 5 0.5
echo "\nRust"
time build/testBilateral_rust 10000 5 0.5
