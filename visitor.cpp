#include <iostream>
#include <unordered_map>
#include "ast.h"
#include "visitor.h"

using namespace std;

// Acepta un visitor sobre una expresión binaria
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

// Acepta un visitor sobre un literal entero
int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

// Acepta un visitor sobre una variable
int IdExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

// Acepta un visitor sobre una asignación
int AssignStmt::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

// Acepta un visitor sobre un print
int PrintStmt::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

// Acepta un visitor sobre un if
int IfStmt::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

// Acepta un visitor sobre un while
int WhileStmt::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

// Crea el generador de código, que escribe el ensamblador en out
GencodeVisitor::GencodeVisitor(ostream& out) : out(out) {}

// Genera el código de left op right y deja el resultado en %rax
int GencodeVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    out << "pushq %rax" << endl;
    exp->right->accept(this);
    out << "movq %rax, %rcx" << endl;
    out << "popq %rax" << endl;
    switch (exp->op) {
        case PLUS_OP:
            out << "addq %rcx, %rax" << endl;
            break;
        case MINUS_OP:
            out << "subq %rcx, %rax" << endl;
            break;
        case MUL_OP:
            out << "imulq %rcx, %rax" << endl;
            break;
        case LE_OP:
            out << "cmpq %rcx, %rax" << endl;
            out << "setle %al" << endl;
            out << "movzbq %al, %rax" << endl;
            break;

        default:
            break;
    }
    return 0;
}

// Carga el literal en %rax
int GencodeVisitor::visit(NumberExp* exp) {
    out << "movq $" << exp->value << ", %rax" << endl;
    return 0;
}

// Carga el valor de la variable desde la pila en %rax
int GencodeVisitor::visit(IdExp* exp) {
    out << "movq " << posicion[exp->value] * -8 << "(%rbp), %rax" << endl;
    return 0;
}

// Evalúa la expresión y la guarda en la posición de la variable (asignada la primera vez)
void GencodeVisitor::visit(AssignStmt* stm) {
    stm->e->accept(this);
    if (!posicion.count(stm->id)) {
        posicion[stm->id] = contador;
        contador++;
    }
    out << "movq %rax, " << posicion[stm->id] * -8 << "(%rbp)" << endl;
}

// Evalúa la expresión y la imprime con printf
void GencodeVisitor::visit(PrintStmt* stm) {
    stm->e->accept(this);
    out << "movq %rax, %rsi" << endl;
    out << "leaq print_fmt(%rip), %rdi" << endl;
    out << "movl $0, %eax" << endl;
    out << "call printf@PLT" << endl;
}

// Genera el código del if (por implementar)
void GencodeVisitor::visit(IfStmt* stm) {
   stm->condicion->accept(this);
   out << "cmpq $0, %rax" << endl;
   out << "je else_0" << endl;
   for(auto i:stm->thenList){
    i->accept(this);
   }
   out << "jmp endif_0" << endl;
   out << "else_0:" << endl;
   for(auto i:stm->elseList){
    i->accept(this);
   }
   out << "endif_0:" << endl;
}

// Genera el código del while (por implementar)
void GencodeVisitor::visit(WhileStmt* stm) {
    out << "while_0";
    stm->condicion->accept(this);
    out << "cmpq $0, %rax" << endl;
    out << "je endwhile_0" << endl;
    for (auto s : stm->body) {   // ajusta el nombre al campo real de tu WhileStmt
        s->accept(this);
    }
    out << "jmp while_0" << endl;
    out << "endwhile_0:" << endl;
}



// Genera el programa completo: datos, prólogo de main, sentencias y epílogo
void GencodeVisitor::gencode(Program* program) {
    out << ".data" << endl;
    out << "print_fmt:.string \"%ld\\n\" " << endl;
    out << ".text" << endl;
    out << ".globl main" << endl;
    out << "main:" << endl;
    out << "pushq %rbp" << endl;
    out << "movq %rsp, %rbp" << endl;
    out << "subq $64, %rsp" << endl;
    for (Stmt* s : program->slist) {
        s->accept(this);
    }
    out << "movq $0, %rax" << endl;
    out << "leave" << endl;
    out << "ret" << endl;
    out << ".section .note.GNU-stack,\"\",@progbits" << endl;
}
