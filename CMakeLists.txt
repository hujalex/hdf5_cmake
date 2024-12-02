cmake_minimum_required(VERSION 3.20)
project(UseHighFive)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# find_package(HighFive REQUIRED)
add_executable(dummy dummy.cpp)

add_subdirectory(HighFive)

target_include_directories(
    dummy
    PUBLIC "${CMAKE_SOURCE_DIR}/HighFive/include"
)
target_link_libraries(dummy HighFive)
# set_target_properties(dummy PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}") // ! Not reliable


# # Set minimum required version of CMake
# cmake_minimum_required(VERSION 3.10)

# # Project Name
# project(HDF5Example)

# # Specify the C++ standard
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Include directories (add your header files' directories here)
# include_directories(${CMAKE_SOURCE_DIR}/include)

# # Add source files
# set(SOURCE_FILES hdf52.cpp)

# # Declare the executable
# add_executable(hdf5_example ${SOURCE_FILES})

# # If you need to link external libraries like HDF5, specify them here
# find_package(HDF5 REQUIRED)
# target_link_libraries(hdf5_example PRIVATE HDF5::HDF5)

# # Optional: set the output directory for binaries
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# # If there are any special flags needed for the build, you can set them here:
# # For example, include a specific compile flag for debugging:
# # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
