.section .data
sdmid:  .ascii "000111", "\0\0\0"     # 每组数据的流水号（可以从1开始编号） 
sda:    .long  512   # 状态信息a
sdb:    .long  -1023    # 状态信息b
sdc:    .long  1265     # 状态信息c
sf:     .long  0        # 处理结果f
        .ascii  "000222","\0\0\0" 
        .long  256809      # 状态信息a
        .long  -1023    # 状态信息b
        .long  2780     # 状态信息c
        .long  0        # 处理结果f
       .ascii  "000333","\0\0\0" 
        .long  2513# 状态信息a
        .long  1265    # 状态信息b
        .long  1023     # 状态信息c
        .long  0        # 处理结果f
       .ascii  "000444","\0\0\0" 
        .long  512   # 状态信息a
        .long  -1023    # 状态信息b
        .long  1265     # 状态信息c
        .long  0        # 处理结果f
        .ascii "555555","\0\0\0"
        .long  2513
        .long  1265
        .long  1023
        .long  0
        .ascii "666666","\0\0\0"
        .long 256800
        .long -2000
        .long 1000
        .long 0
        num = 6
midf:  .fill  9, 1, 0 
        .long 0, 0, 0, 0
        .fill  9, 1, 0
        .long 0,0,0,0
        .fill 9, 1,0
        .long 0,0,0,0
highf: .fill  9, 1, 0 
        .long 0, 0, 0, 0
        .fill  9, 1, 0
        .long 0,0,0,0
        .fill 9,1,0
        .long 0,0,0,0
lowf:   .fill  9, 1, 0 
        .long 0, 0, 0, 0
        .fill  9, 1, 0
        .long 0,0,0,0
        .fill 9,1,0
        .long 0,0,0,0
len=25
.section .text
.global     _start
_start:
    mov %esp, %ebp
    sub $0x20, %esp
    movl $midf, -0x4(%ebp)
    movl $highf, -0x8(%ebp)
    movl $lowf, -0xc(%ebp)
    mov $num, %cl
    leal sdmid, %esi
    loop1:
    call calculate
    movl %edx, 21(%esi)
    cmp $0, %eax
    jle lee
    movl -0x8(%ebp), %edi
    call copy_data
    addl $13, -0x8(%ebp)
    jmp con
    lee:
    cmp $0, %eax
    je ee
    mov -0xc(%ebp), %edi
    call copy_data
    addl $13, -0xc(%ebp)
    jmp con
    ee:
    mov -0x4(%ebp), %edi
    call copy_data
    addl $13, -0x4(%ebp)
    con:
    add $25, %esi
    dec %cl
    jnz loop1
    mov $1, %eax
    mov $0, %ebx
    int $0x80
.type calculate @function
calculate:
    push %esi
    mov 9(%esi), %eax
    imul $5, %eax
    add 13(%esi), %eax 
    sub 17(%esi), %eax
    add $100, %eax
    sar $7, %eax
    mov %eax, %edx
    cmp $100, %eax
    jle le
    mov $1, %eax
    jmp end
    le:
    cmp $100, %eax
    je eq
    mov $-1, %eax
    jmp end
    eq:
    mov $0, %eax
    jmp end
    end:
    pop %esi
    ret


.type copy_data @function
copy_data:
    push %ecx
    push %esi
    push %edi
    mov $2, %cl
    loop2:
    movl (%esi), %ebx
    movl %ebx, (%edi)
    addl $4, %esi
    addl $4, %edi
    dec %cl
    jnz loop2
    movb (%esi), %bl
    movb %bl, (%edi)
    addl $13, %esi
    addl $1, %edi
    movl (%esi), %ebx
    movl %ebx, (%edi)
    pop %edi
    pop %esi
    pop %ecx
    ret
ret
