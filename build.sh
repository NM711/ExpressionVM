make clean
make frontend
make runtime
make main.out

mkdir build
mkdir build/depen

mv *.o ./build/depen/
mv main.out ./build
