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

int DoWhileStmt::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int IfExp::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int BreakStmt::accept(Visitor* visitor) {
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
    int n = labelCount++;
    stm->condicion->accept(this);
    out << "cmpq $0, %rax" << endl;
    out << "je else_" << n << endl;
    for (auto s : stm->thenList) s->accept(this);
    out << "jmp endif_" << n << endl;
    out << "else_" << n << ":" << endl;
    for (auto s : stm->elseList) s->accept(this);
    out << "endif_" << n << ":" << endl;
}

// Genera el código del while (por implementar)
void GencodeVisitor::visit(WhileStmt* stm) {
    int n = labelCount++;
    out << "while_" << n << ":" << endl;
    stm->condicion->accept(this);
    out << "cmpq $0, %rax" << endl;
    out << "je endwhile_" << n << endl;
    breakLabels.push_back("endwhile_" + to_string(n));
    for (auto s : stm->body) s->accept(this);
    breakLabels.pop_back();
    out << "jmp while_" << n << endl;
    out << "endwhile_" << n << ":" << endl;
}

// Se genera el codigo para do while
void GencodeVisitor::visit(DoWhileStmt* stm) {
    int n = labelCount++;
    out << "do_" << n << ":" << endl;
    breakLabels.push_back("enddowhile_" + to_string(n)); // destino de un break
    for (auto s : stm->body) s->accept(this);
    breakLabels.pop_back();
    stm->condicion->accept(this);
    out << "cmpq $0, %rax" << endl;
    out << "jne do_" << n << endl;                       // se repite si es verdadero
    out << "enddowhile_" << n << ":" << endl;
}

// De acuerdo a la condicion, se genera el codigo para ifexp
int GencodeVisitor::visit(IfExp* exp) {
    int n = labelCount++;
    exp->cond->accept(this);
    out << "cmpq $0, %rax" << endl;
    out << "je ifexp_else_" << n << endl;
    exp->thenExp->accept(this);
    out << "jmp ifexp_end_" << n << endl;
    out << "ifexp_else_" << n << ":" << endl;
    exp->elseExp->accept(this);
    out << "ifexp_end_" << n << ":" << endl;
    return 0;
}


void GencodeVisitor::visit(BreakStmt* stm) {
    if (breakLabels.empty())
        throw runtime_error("break fuera de un bucle");
    out << "jmp " << breakLabels.back() << endl;
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
