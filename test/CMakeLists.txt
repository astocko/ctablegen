include_directories(${CMAKE_SOURCE_DIR}/src)

add_definitions(${LLVM_CPP_FLAGS})

set(TEST_CXX_FLAGS "${LLVM_CXX_FLAGS} -fexceptions")
list(REMOVE_ITEM TEST_CXX_FLAGS "-fno-exceptions")

add_executable(tblgentest test.cc)
set_target_properties(tblgentest PROPERTIES COMPILE_FLAGS "${TEXT_CXX_FLAGS}")

file(TO_NATIVE_PATH "${TG_INCLUDE_DIR}/Target/X86/X86.td" TG_X86_TD)
file(TO_NATIVE_PATH "${TG_INCLUDE_DIR}/Target/X86" TG_X86_INC1)
file(TO_NATIVE_PATH "${TG_INCLUDE_DIR}/../include" TG_X86_INC2)
set(LLVM_X86_TEST_CFG "${PROJECT_BINARY_DIR}/test_config.cfg")
file(WRITE ${LLVM_X86_TEST_CFG} "${TG_X86_TD}\n")
file(APPEND ${LLVM_X86_TEST_CFG} "${TG_X86_INC1}\n")
file(APPEND ${LLVM_X86_TEST_CFG} "${TG_X86_INC2}")

target_link_libraries(
  tblgentest
  ctablegen
  "${LLVM_LIB_DIR}/libLLVMCore.a"
  "${LLVM_LIB_DIR}/libLLVMSupport.a"
  "${LLVM_SYS_LIBS}"
  )
