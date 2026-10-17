.data
print_fmt:.string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
movq $1, %rax
movq %rax, -8(%rbp)
movq $0, %rax
movq %rax, -16(%rbp)
movq $0, %rax
movq %rax, -24(%rbp)
do_0:
movq -16(%rbp), %rax
pushq %rax
movq -8(%rbp), %rax
pushq %rax
movq $4, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_1
movq -8(%rbp), %rax
pushq %rax
movq $2, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
jmp ifexp_end_1
ifexp_else_1:
movq $0, %rax
ifexp_end_1:
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -16(%rbp)
movq -24(%rbp), %rax
pushq %rax
movq -8(%rbp), %rax
pushq %rax
movq $4, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_2
movq $0, %rax
jmp ifexp_end_2
ifexp_else_2:
movq -8(%rbp), %rax
ifexp_end_2:
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -24(%rbp)
movq $7, %rax
pushq %rax
movq -8(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_3
jmp enddowhile_0
jmp endif_3
else_3:
endif_3:
movq -8(%rbp), %rax
pushq %rax
movq $1, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -8(%rbp)
movq $1, %rax
cmpq $0, %rax
jne do_0
enddowhile_0:
movq -16(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -24(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -16(%rbp), %rax
pushq %rax
movq -24(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je ifexp_else_4
movq -24(%rbp), %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
subq %rcx, %rax
jmp ifexp_end_4
ifexp_else_4:
movq -16(%rbp), %rax
pushq %rax
movq -24(%rbp), %rax
movq %rax, %rcx
popq %rax
subq %rcx, %rax
ifexp_end_4:
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits
