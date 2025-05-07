cmake_minimum_required(VERSION 3.22)
project(graph)

set(CMAKE_CXX_STANDARD 17)

# === Eigen include path ===
include_directories("C:/Users/USER/Downloads/eigen-3.4.0/eigen-3.4.0")

# === SDL2 paths ===
set(SDL2_DIR "C:/Users/USER/CLionProjects/project/SDL2-devel-2.30.8-mingw/SDL2-2.30.8/x86_64-w64-mingw32")
set(SDL2_TTF_DIR "C:/Users/USER/CLionProjects/project/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
set(SDL2_IMAGE_DIR "C:/Users/USER/CLionProjects/project/SDL2_image-2.8.2/x86_64-w64-mingw32")

# === SDL2 includes and libraries ===
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include/SDL2")
set(SDL2_TTF_INCLUDE_DIR "${SDL2_TTF_DIR}/include/SDL2")
set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_DIR}/include/SDL2")
set(SDL2_LIBRARY "${SDL2_DIR}/lib/libSDL2main.a" "${SDL2_DIR}/lib/libSDL2.a")
set(SDL2_TTF_LIBRARY "${SDL2_TTF_DIR}/lib/libSDL2_ttf.a")
set(SDL2_IMAGE_LIBRARY "${SDL2_IMAGE_DIR}/lib/libSDL2_image.a")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# Add executable
add_executable(${PROJECT_NAME} main.cpp
        Component.cpp
        Component.h
        Circuit.cpp
        Circuit.h
        MatrixAnalyzer.cpp
        MatrixAnalyzer.h
        CommandInterface.cpp
        CommandInterface.h
)

# Link SDL2, SDL2_ttf, SDL2_image, and Windows system libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        -lmingw32
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        -lsetupapi
        -limm32
        -lwinmm
        -lversion
        -ldinput8
        -ldxguid
        -ldxerr8
        -luser32
        -lgdi32
        -lole32
        -loleaut32
        -luuid
        -ladvapi32
        -lshell32
        -lrpcrt4
)



#cmake_minimum_required(VERSION 3.22)
#project(graph)
#
#set(CMAKE_CXX_STANDARD 17)
#
## Set the path to SDL2
#set(SDL2_DIR "C:/Users/USER/CLionProjects/project/SDL2-devel-2.30.8-mingw/SDL2-2.30.8/x86_64-w64-mingw32")
#
## Set the path to SDL2_ttf
#set(SDL2_TTF_DIR "C:/Users/USER/CLionProjects/project/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
#
## Set the path to SDL2_image
#set(SDL2_IMAGE_DIR "C:/Users/USER/CLionProjects/project/SDL2_image-2.8.2/x86_64-w64-mingw32")
#
## Specify SDL2, SDL2_ttf, and SDL2_image include directories
#set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include/SDL2")
#set(SDL2_TTF_INCLUDE_DIR "${SDL2_TTF_DIR}/include/SDL2")
#set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_DIR}/include/SDL2")
#
## Specify SDL2, SDL2_ttf, and SDL2_image library files
#set(SDL2_LIBRARY "${SDL2_DIR}/lib/libSDL2main.a" "${SDL2_DIR}/lib/libSDL2.a")
#set(SDL2_TTF_LIBRARY "${SDL2_TTF_DIR}/lib/libSDL2_ttf.a")
#set(SDL2_IMAGE_LIBRARY "${SDL2_IMAGE_DIR}/lib/libSDL2_image.a")
#
## Include SDL2, SDL2_ttf, and SDL2_image headers
#include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
#
## Add executable
#add_executable(${PROJECT_NAME} main.cpp
#        Component.cpp
#        Component.h
#        Circuit.cpp
#        Circuit.h
#        MatrixAnalyzer.cpp
#        MatrixAnalyzer.h
#        CommandInterface.cpp
#        CommandInterface.h
#)
#
## Link SDL2, SDL2_ttf, SDL2_image, and Windows system libraries
#target_link_libraries(${PROJECT_NAME} PRIVATE
#        -lmingw32
#        ${SDL2_LIBRARY}
#        ${SDL2_TTF_LIBRARY}
#        ${SDL2_IMAGE_LIBRARY}
#        -lsetupapi
#        -limm32
#        -lwinmm
#        -lversion
#        -ldinput8
#        -ldxguid
#        -ldxerr8
#        -luser32
#        -lgdi32
#        -lole32
#        -loleaut32
#        -luuid
#        -ladvapi32
#        -lshell32
#        -lrpcrt4
#)
