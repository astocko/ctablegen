cmake_minimum_required(VERSION 3.4.3)
set(CMAKE_CXX_STANDARD 11)
project(libctablegen CXX)

include("cmake/macros.cmake")

# Configuration
if(LLVM_CONFIG_BIN)
  get_filename_component(LLVM_CONFIG_NAME ${LLVM_CONFIG_BIN} NAME)
  get_filename_component(LLVM_CONFIG_DIR ${LLVM_CONFIG_BIN} DIRECTORY)
  find_program(LLVM_CONFIG ${LLVM_CONFIG_NAME} ${LLVM_CONFIG_DIR})
else ()
  find_program(LLVM_CONFIG "llvm-config")
endif ()


if (NOT LLVM_CONFIG)
  message(FATAL_ERROR "llvm-config could not be found")
endif ()

# Get required LLVM configuration parameters
llvm_config(LLVM_VER "--version")
llvm_config(LLVM_INCLUDE_DIRS "--includedir")
llvm_config(LLVM_LIB_DIR "--link-static;--libdir")
llvm_config(LLVM_CPP_FLAGS "--link-static;--cppflags")
llvm_config(LLVM_CXX_FLAGS "--link-static;--cxxflags")

# Get correct sources for specified LLVM version
file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}/third-party/llvm-${LLVM_VER}/lib" TG_INCLUDE_DIR)
file(TO_CMAKE_PATH "${TG_INCLUDE_DIR}/TableGen" TG_SOURCE_DIR)
set(TG_CPP_FILES Error.cpp Record.cpp SetTheory.cpp StringMatcher.cpp TGLexer.cpp TGParser.cpp)
prepend_dir(TG_SOURCES "${TG_SOURCE_DIR}" "${TG_CPP_FILES}")

add_subdirectory(src)
