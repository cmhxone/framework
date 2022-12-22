cmake_minimum_required(VERSION 3.0.0)
project(framework VERSION 0.1.0)

include(CTest)
enable_testing()

# Using standard C++20
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)
set(CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Copy INI files to cmake binary path
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/config.ini ${CMAKE_BINARY_DIR}/resources/config.ini COPYONLY)

# Configure exclude path
set(EXCLUDE_PATHS "CMakeFiles" "build")
# Find whole files
file(GLOB_RECURSE SOURCE_FILES "*.cc" "*.hh")

# Filter exclude files
foreach(TMP_VAR ${SOURCE_FILES})
    foreach(EXCLUDE_PATH ${EXCLUDE_PATHS})
        string(FIND ${TMP_VAR} ${EXCLUDE_PATH} RESULT)
        if(NOT ${RESULT} EQUAL -1)
            list(REMOVE_ITEM SOURCE_FILES ${TMP_VAR})
        endif()
    endforeach(EXCLUDE_PATH)
endforeach(TMP_VAR)
message(${SOURCE_FILES})

# Compile binary executable
add_executable(framework ${SOURCE_FILES})

target_link_libraries(framework ${CONAN_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)