cmake_minimum_required(VERSION 3.10)
project(Capston)

set(CMAKE_CXX_STANDARD 14)

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS net core base media)

# Include the wxWidgets use file to set up variables pointing to wxWidgets libraries and include files
include(${wxWidgets_USE_FILE})

# Add the source files
set(SOURCE_FILES main.cpp VideoPlayer.cpp ImageSlideshow.cpp)

# Add the executable
add_executable(Capston ${SOURCE_FILES})

# Link the wxWidgets libraries
target_link_libraries(Capston ${wxWidgets_LIBRARIES})

# Add the wxWidgets include directory
include_directories(/usr/local/include/wx-3.1)