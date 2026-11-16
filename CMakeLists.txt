cmake_minimum_required(VERSION 4.3)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(projet1_nsi)

# --- Build type ---
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    message(STATUS "No build type specified. Defaulting to Debug.")
endif ()

# --- Language standard ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Compiler flags ---
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Wextra -Wshadow -fsanitize=address,undefined -g3 -fno-omit-frame-pointer -fno-lto")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -Wall -Wextra -Wshadow -g3 -fno-omit-frame-pointer -flto=thin -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Wshadow -flto=thin -march=native -DNDEBUG")
add_compile_options(-stdlib=libc++ -fdiagnostics-color=always -fdiagnostics-show-template-tree -fstandalone-debug)
add_link_options(-flto=thin -fuse-ld=lld -stdlib=libc++)

# --- Sources ---
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

add_library(lib ${LIB_SOURCES})
target_include_directories(lib PUBLIC ${CMAKE_SOURCE_DIR}/src)

# --- Executable ---
add_executable(projet1_nsi src/main.cpp)
target_link_libraries(projet1_nsi PRIVATE lib)

# --- External libraries ---
include(FetchContent)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG v5.3.3
)
FetchContent_MakeAvailable(unordered_dense)

target_link_libraries(lib PUBLIC unordered_dense)
