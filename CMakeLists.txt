cmake_minimum_required(VERSION 3.9)
project(DS_Wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DS_Wet2 main.cpp HTable.h RTree.h TNode.h UFind.h library.h Pixel.cpp Pixel.h LNode.h List.h)