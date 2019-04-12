cmake_minimum_required(VERSION 3.12)
project(OJcodes)

set(CMAKE_CXX_STANDARD 14)

include_directories(DataStructure)

add_executable(OJcodes
        DataStructure/ListNode.cpp
        DataStructure/ListNode.h
        DataStructure/TreeNode.cpp
        DataStructure/TreeNode.h
        Leetcode/isSameTree/isSameTree.cpp
        Leetcode/Merge/Merge.cpp
        Test/test0/test0.cpp
        OJcodes.cpp)
