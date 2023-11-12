clang --target=x86_64-windows-msvc -nostdlib -ffreestanding -c .\src\arch\arch_x64.c -I include -o .\build\arch.o
clang --target=x86_64-windows-msvc -nostdlib -ffreestanding -c .\src\platform\platform_windows.c -I include -o .\build\platform.o
clang --target=x86_64-windows-msvc -nostdlib -ffreestanding -c .\research\win_playground.c -I include -g3 -o .\build\playground.o
clang -v --target=x86_64-windows-msvc -fuse-ld=lld-link -nostdlib -ffreestanding -g3 --for-linker "/entry:_start" --for-linker "/subsystem:console" .\build\*.o -o .\build\pl.exe