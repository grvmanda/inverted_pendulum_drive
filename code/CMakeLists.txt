CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set (CMAKE_CXX_STANDARD 14)

# set the project name
project(InvertedPendulum)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main_alg.cpp
    src/BNO055.cpp
)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(InvertedPendulum
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/inc

)

# link the i2c library
# FYI: https://stackoverflow.com/questions/63890499/how-to-link-dynamic-library-li2c-with-cmake-undefined-reference-to-i2c-smb
target_link_libraries(InvertedPendulum i2c)