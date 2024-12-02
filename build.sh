# rm *h5
cmake -DCMAKE_INSTALL_PREFIX=build/install -DHIGHFIVE_USE_BOOST=Off -B build .
cmake --build build --parallel
cmake --install build
cmake -DCMAKE_PREFIX_PATH="${HDF5_ROOT};${HIGHFIVE_ROOT}" -B build .
cmake --build build --verbose
cd build
make
time ./dummy
cd ..