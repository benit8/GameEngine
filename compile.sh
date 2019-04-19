#!/bin/sh

bin="exe"

# does `./build` directory exists ?
if [ ! -d ./build ]; then
	mkdir ./build
fi

# does the zia bin exists ?
# if [ -f "./$bin" ]; then
# 	rm "./$bin"
# fi

cd ./build &&
cmake .. -G "Unix Makefiles" &&
cmake --build . -- -j $(nproc) &&

# we still in ./build
cp "./$bin" ../