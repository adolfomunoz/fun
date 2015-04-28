cmake_minimum_required(VERSION 2.4)
add_definitions(-mtune=native)
add_definitions(-Wall)
add_definitions(-O3)

add_definitions(-std=c++14)
add_executable(fun-dot    examples/fun-dot.cc)
add_executable(fun-norm   examples/fun-norm.cc)
add_executable(fun-primes examples/fun-primes.cc)
