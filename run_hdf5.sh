rm *h5
for i in {1..1000}
do 
    cd build
    # Run the executable and capture its memory usage

    time ./dummy
    # ls -lh "../double_foo.h5"
    ls -lh "../float32_foo.h5"
    cd ..
done