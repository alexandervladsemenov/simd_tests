- clone the repo
- inside the repo: `mkdir build; cd build; cmake ..; make`
- cd ..; sh run.sh

If your compiler is gcc, the C++ with SIMD code should produce a binary which uses SIMD exponent calls (_ZGVdN8v_expf@pl and _ZGVbN4v_expf@pl on x64 architecture)

If your compiler is clang, however, then it won't optimize the code to use the SIMD calls.
