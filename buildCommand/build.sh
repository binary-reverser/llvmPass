# config the llvm
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=~/bin/llvm_s ../llvm
# run pass
./bin/opt -load lib/LLVMHello.so  -hello test.bc
# gen ll
clang -emit-llvm -S test.mm -o test.ll
