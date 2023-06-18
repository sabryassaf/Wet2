cmake_minimum_required(VERSION 3.21)
project(WET2DS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WET2DS
        AVLNode.h
        mainWet2.cpp
        RankTree.h
        recordsCompany.h
        utilesWet2.h
        Customer.h  HashTable.h recordsCompany.cpp RecordsUnionSabry.h Record.h)
