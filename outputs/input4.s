.data
print_fmt:.string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
movq $20, %rax
movq %rax, -8(%rbp)
do_0:
movq -8(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -8(%rbp), %rax
pushq %rax
movq $5, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax, -8(%rbp)
movq -8(%rbp), %rax
pushq %rax
movq $15, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
jne do_0
enddowhile_0:
movq $1, %rax
movq %rax, -16(%rbp)
while_0:
movq $1, %rax
cmpq $0, %rax
je endwhile_0
movq -16(%rbp), %rax
pushq %rax
movq $2, %rax
movq %rax, %rcx
popq %rax
imulq %rcx, %rax
movq %rax, -16(%rbp)
movq $16, %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
setle %al
movzbq %al, %rax
cmpq $0, %rax
je else_1
jmp endwhile_0
jmp endif_1
else_1:
endif_1:
jmp while_0
endwhile_0:
movq -16(%rbp), %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
movq -8(%rbp), %rax
pushq %rax
movq -16(%rbp), %rax
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
