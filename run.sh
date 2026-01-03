echo "C++ with no SIMD exponent"
time build/testBilateral_cpp_no_simd 10000 5 0.5
echo "\nC++ with SIMD exponent"
time build/testBilateral_cpp 10000 5 0.5
echo "\nC++ with improved SIMD exponent"
time build/testBilateral_cpp_simd_improved 10000 5 0.5
echo "\nFortran"
time build/testBilateral_fortran 10000 5 0.5
echo "\nRust Slow"
time build/testBilateral_rust_slow 10000 5 0.5
echo "\nRust Fast"
time build/testBilateral_rust_fast 10000 5 0.5
