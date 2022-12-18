cmake_minimum_required(VERSION 3.0.0)
project(framework VERSION 0.1.0)

include(CTest)
enable_testing()

# Using standard C++20
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)
set(CXX_STANDARD 20)

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

# use pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 sdl2 REQUIRED)
pkg_check_modules(SDL2IMAGE sdl2_image REQUIRED)
pkg_check_modules(SDL2MIXER sdl2_mixer REQUIRED)
pkg_check_modules(SDL2TTF sdl2_ttf REQUIRED)
pkg_check_modules(GLOG libglog REQUIRED)
pkg_check_modules(GFLAGS gflags REQUIRED)
pkg_check_modules(INIH inih REQUIRED)
pkg_check_modules(INIREADER INIREADER REQUIRED)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

# Header paths
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2MIXER_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
    ${GLOG_INCLUDE_DIRS}
    ${GFLAGS_INCLUDE_DIRS}
    ${INIH_INCLUDE_DIRS}
    ${INIREADER_INCLUDE_DIRS}
)

# Compile binary executable
add_executable(framework ${SOURCE_FILES})

# Library paths
target_link_directories(
    framework PUBLIC
    ${SDL2_LIBRARY_DIRS}
    ${SDL2IMAGE_LIBRARY_DIRS}
    ${SDL2MIXER_LIBRARY_DIRS}
    ${SDL2TTF_LIBRARY_DIRS}
    ${GLOG_LIBRARY_DIRS}
    ${GFLAGS_LIBRARY_DIRS}
    ${INIH_LIBRARY_DIRS}
    ${INIREADER_LIBRARY_DIRS}
)
# Link libraries
target_link_libraries(
    framework
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${GLOG_LIBRARIES}
    ${GFLAGS_LIBRARIES}
    ${INIH_LIBRARIES}
    ${INIREADER_LIBRARIES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)