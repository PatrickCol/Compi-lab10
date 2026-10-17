.data
print_fmt:.string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
movq $15, %rax
movq %rax, -8(%rbp)
movq $25, %rax
movq %rax, -16(%rbp)
movq $0, %rax
movq %rax, -24(%rbp)
movq -8(%rbp), %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_0
movq -16(%rbp), %rax
pushq %rax
movq $20, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_0
movq $1, %rax
movq %rax, -24(%rbp)
jmp endif_0
else_0:
movq $2, %rax
movq %rax, -24(%rbp)
endif_0:
jmp endif_0
else_0:
movq $3, %rax
movq %rax, -24(%rbp)
endif_0:
movq -24(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -24(%rbp), %rax
pushq %rax
movq $1, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_0
movq -8(%rbp), %rax
pushq %rax
movq $100, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -8(%rbp)
jmp endif_0
else_0:
movq -8(%rbp), %rax
pushq %rax
movq $200, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -8(%rbp)
endif_0:
movq -8(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits
