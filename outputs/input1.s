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
do_0:
movq -16(%rbp), %rax
pushq %rax
movq -8(%rbp), %rax
pushq %rax
movq $3, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -16(%rbp)
movq -8(%rbp), %rax
pushq %rax
movq $1, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -8(%rbp)
movq -8(%rbp), %rax
pushq %rax
movq $4, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
jne do_0
enddowhile_0:
movq -16(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -8(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits
