.data
print_fmt:.string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
movq $10, %rax
pushq %rax
movq $5, %rax
movq %rax, %rcx
popq %rax
subq %rcx, %rax
movq %rax, -8(%rbp)
movq $4, %rax
pushq %rax
movq $5, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
movq %rax, -16(%rbp)
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
movq $0, %rax
leave
ret
.section .note.GNU-stack,"",@progbits
