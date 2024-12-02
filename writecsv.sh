rm *csv
g++ writecsv.cpp -o writecsv.exe

for i in {1..1000}
do
time ./writecsv.exe
ls -lh "data.csv"
done