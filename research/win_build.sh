__c_flags="-g2 --target=x86_64-windows-msvc -nostdlib -ffreestanding"
__build_obj="./target/x86_64-windows-msvc/obj"
__build_out="./target/x86_64-windows-msvc"
__cc="clang"

mkdir -p $__build_obj
$__cc $__c_flags -c ./src/platform/platform_windows.c -I include -o $__build_obj/platform.o                                                
$__cc $__c_flags -c ./src/platform/platform_generic.c -I include -o $__build_obj/platform_gen.o                                                
$__cc $__c_flags -c ./src/arch/arch_x64.c -I include -o $__build_obj/arch.o                                                
$__cc $__c_flags -c ./src/allocator/allocator_os.c -I include -o $__build_obj/allocator_os.o                                                
$__cc $__c_flags -c ./research/generic_playground.c -I include  -o $__build_obj/playground.o                                          
$__cc $__c_flags -fuse-ld=lld-link -nostdlib --for-linker "/entry:_start" --for-linker "/subsystem:console" $__build_obj/*.o -o $__build_out/pl.exe

