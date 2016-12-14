# Build
cmake -DLLVM_CONFIG_BIN=llvm-config-3.9 ..

# Compile Commands
cmake -DLLVM_CONFIG_BIN=llvm-config-3.9 -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
