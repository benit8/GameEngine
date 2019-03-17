#!/bin/sh

bin="exe"

# does `./build` directory exists ?
if [ -d ./build ]; then
	rm -rf ./build
fi

# does the zia bin exists ?
if [ -f "./$bin" ]; then
	rm "./$bin"
fi

ncore=$(echo "`grep -c ^processor /proc/cpuinfo`+1" | bc)

mkdir ./build && cd ./build &&
# conan install .. --build=missing &&
cmake .. -G "Unix Makefiles" &&
cmake --build . -- -j "$ncore" &&

# we still in ./build
cp "./$bin" ../