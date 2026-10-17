.data
print_fmt:.string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
movq $0, %rax
movq %rax, -8(%rbp)
movq $1, %rax
movq %rax, -16(%rbp)
movq $0, %rax
movq %rax, -24(%rbp)
movq -8(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -16(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
while_0:
movq $1, %rax
cmpq $0, %rax
je endwhile_0
movq -8(%rbp), %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -32(%rbp)
movq -16(%rbp), %rax
movq %rax, -8(%rbp)
movq -32(%rbp), %rax
movq %rax, -16(%rbp)
movq -24(%rbp), %rax
pushq %rax
movq $1, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -24(%rbp)
movq -32(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq $20, %rax
pushq %rax
movq -32(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_0
jmp endwhile_0
jmp endif_0
else_0:
endif_0:
jmp while_0
endwhile_0:
movq -24(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -24(%rbp), %rax
pushq %rax
movq $5, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_0
movq $999, %rax
jmp endif_0
else_0:
movq -32(%rbp), %rax
pushq %rax
movq $2, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
endif_0:
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits
