cmake_minimum_required(VERSION 3.16)

project(MiniSearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(SearchEngine
    src/main.cpp
    src/Document.cpp
    src/DocumentLoader.cpp
    src/Tokenizer.cpp
    src/InvertedIndex.cpp
)