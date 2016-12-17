# Helpers

# Configure compiler
include_directories(${LLVM_INCLUDE_DIRS} ${TG_INCLUDE_DIR})
add_definitions(${LLVM_CPP_FLAGS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")

# Create library
add_library(ctablegen ${TG_SOURCES} Utility.cc RecordVal.cc Record.cc RecordMap.cc RecordKeeper.cc TableGen.cc)

set(LLVM_LIB_DIR_CFG "${PROJECT_BINARY_DIR}/llvm_lib_dir.cfg")

file(WRITE ${LLVM_LIB_DIR_CFG} "${LLVM_LIB_DIR}\n")
file(APPEND ${LLVM_LIB_DIR_CFG} "${LLVM_SYS_LIBS}")

# Install
install(TARGETS ctablegen DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${LLVM_LIB_DIR_CFG} DESTINATION ${CMAKE_INSTALL_PREFIX})
