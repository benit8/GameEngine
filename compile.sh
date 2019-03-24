#!/bin/sh

ncore=$(echo "`grep -c ^processor /proc/cpuinfo`+1" | bc)
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
cmake --build . -- -j "$ncore" &&

# we still in ./build
cp "./$bin" ../