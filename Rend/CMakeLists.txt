# CMakeList.txt : CMake project for Rend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Rend "main.cpp" "Window.cpp" "Geometry.h")

# TODO: Add tests and install targets if needed.
install (TARGETS Rend DESTINATION "Rend/bin")