def win(a):
    r=1
    if a & 0x1:
        r*=2
    if a & 0x2:
        r*= (2+ (~a&0x1)*6 )
    if a & 0x4:
        r*=0x10
    return r

print(hex(win(0x1))) #read
print(hex(win(0x2))) #write
print(hex(win(0x4))) #execute
print(hex(win(0x1 | 0x2))) # read write
print(hex(win(0x1 | 0x4))) # read execute
print(hex(win(0x1 | 0x2 | 0x4)))  # read write execute
print(hex(win(0x2 | 0x4))) # execute write


# https://doxygen.reactos.org/d1/d03/xdk_2mmtypes_8h_source.html