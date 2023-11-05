__c_flags="-o3 --target=x86_64-windows-msvc -nostdlib -ffreestanding"

clang $__c_flags -c ./src/platform/platform_windows.c -I include -o ./build/platform.o                                                
clang $__c_flags -c ./src/platform/platform_generic.c -I include -o ./build/platform_gen.o                                                
clang $__c_flags -c ./src/arch/arch_x64.c -I include -o ./build/arch.o                                                
clang $__c_flags -c ./research/generic_playground.c -I include  -o ./build/playground.o                                          
clang $__c_flags -fuse-ld=lld-link -nostdlib --for-linker "/entry:_start" --for-linker "/subsystem:console" ./build/*.o -o ./build/pl.exe

