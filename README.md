# ctablegen
Basic C wrapper for LLVM's TableGen. Requires C++ compiler, llvm includes, and llvm-config. Also requires libLLVMCore and libLLVMSupport at runtime.

# Build
mkdir build
cd build
cmake ..

# Specifying llvm-config
cmake -DLLVM_CONFIG_BIN=llvm-config-3.9 ..

# Generate Compile Commands (compile_commands.json)
cmake -DLLVM_CONFIG_BIN=llvm-config-3.9 -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

# LICENSE

