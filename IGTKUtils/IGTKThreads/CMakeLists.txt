# CMakeList.txt : CMake project for IGTKThreads, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB IGTKThreads_SRC
    "*.h"
    "*.cpp"
)

# Add source to this project's executable.
add_executable (IGTKThreads ${IGTKThreads_SRC})

# TODO: Add tests and install targets if needed.
