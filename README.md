- clone the repo
- inside the repo: `mkdir build; cd build; cmake ..; make`
- cd ..; sh run.sh

If your compiler is gcc (v15 or lower), the C++ with SIMD code should produce a binary which uses SIMD exponent calls (_ZGVdN8v_expf@plt and _ZGVbN4v_expf@plt on x64 architecture)

If your compiler is clang (v21 or lower), however, then it won't optimize the code to use the SIMD calls. (build with cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++)

The slow and fast Rust binaries are built from source code that was directly converted from the C++ bilateral.cpp and bilateral_cpp_simd_improved.cpp files, respectively.