cmake_minimum_required(VERSION 3.23)
project(Wet_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wet_2
        AVLNode.h
        mainWet2.cpp
        RankTree.h
        recordsCompany.h
        utilesWet2.h
        Customer.h)
