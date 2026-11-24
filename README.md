To benchmark:
```
cmake --preset benchmarks
cmake --build ./build/
./build/CowStringBenchmarks
```

To test:
```
cmake --preset debug
cmake --build ./build/
ctest --test-dir ./build/
```
