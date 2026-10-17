.data
print_fmt:.string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
movq $7, %rax
movq %rax, -8(%rbp)
movq $12, %rax
movq %rax, -16(%rbp)
movq -8(%rbp), %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_0
movq -8(%rbp), %rax
jmp ifexp_end_0
ifexp_else_0:
movq -16(%rbp), %rax
ifexp_end_0:
movq %rax, -24(%rbp)
movq -16(%rbp), %rax
pushq %rax
movq -8(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_1
movq -8(%rbp), %rax
jmp ifexp_end_1
ifexp_else_1:
movq -16(%rbp), %rax
ifexp_end_1:
movq %rax, -32(%rbp)
movq -24(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -32(%rbp), %rax
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
je ifexp_else_2
movq $100, %rax
jmp ifexp_end_2
ifexp_else_2:
movq -24(%rbp), %rax
pushq %rax
movq $10, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_3
movq $200, %rax
jmp ifexp_end_3
ifexp_else_3:
movq $300, %rax
ifexp_end_3:
ifexp_end_2:
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -8(%rbp), %rax
pushq %rax
movq $10, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_4
movq -8(%rbp), %rax
pushq %rax
movq $2, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
jmp ifexp_end_4
ifexp_else_4:
movq -16(%rbp), %rax
pushq %rax
movq $3, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
ifexp_end_4:
pushq %rax
movq $15, %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_5
movq $50, %rax
jmp ifexp_end_5
ifexp_else_5:
movq $25, %rax
ifexp_end_5:
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits
