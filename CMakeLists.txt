cmake_minimum_required(VERSION 3.26)
project(DecisionTree)

set(CMAKE_CXX_STANDARD 23)
include_directories(lib)


add_executable(DecisionTree
        main.cpp
        lib/DecisionTree.h
        lib/DecisionTreeMetrics.h
        lib/TreeNode.h
        lib/Visualise.h
        lib/parser.hpp
        lib/DataSet.h
        src/DecisionTreeMetrics.cpp
        src/DataSet.cpp
        src/Visualise.cpp
        src/DecisionTree.cpp
)

include_directories(sqlite_orm/include/sqlite_orm)
include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(DecisionTree sqlite3)