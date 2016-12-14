# Helpers

# Configure compiler
include_directories(${LLVM_INCLUDE_DIRS} ${TG_INCLUDE_DIR})
add_definitions(${LLVM_CPP_FLAGS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")

# Create library
add_library(ctblgen STATIC ${TG_SOURCES} TableGenWrapper.cc)

set(LLVM_LIB_DIR_CFG "${PROJECT_BINARY_DIR}/llvm_lib_dir.cfg")

file(WRITE ${LLVM_LIB_DIR_CFG} "${LLVM_LIB_DIR}")

# Install
install(TARGETS ctblgen DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${LLVM_LIB_DIR_CFG} DESTINATION ${CMAKE_INSTALL_PREFIX})
