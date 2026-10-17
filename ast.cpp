#include <iostream>
#include "ast.h"

using namespace std;

// Destructor de Exp
Exp::~Exp() {}

// Devuelve el símbolo de un operador binario
string Exp::binopToChar(BinaryOp op) {
    switch (op) {
        case PLUS_OP:  return "+";
        case MINUS_OP: return "-";
        case MUL_OP:   return "*";
        case DIV_OP:   return "/";
        case POW_OP:   return "**";
        case LE_OP:    return "<=";
        default:       return "?";
    }
}

// Crea una expresión binaria con sus dos operandos
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp o)
    : left(l), right(r), op(o) {}

// Libera los dos operandos
BinaryExp::~BinaryExp() {
    delete left;
    delete right;
}

// Crea un literal entero
NumberExp::NumberExp(int v) : value(v) {}

// Destructor de NumberExp
NumberExp::~NumberExp() {}

// Crea una referencia a una variable
IdExp::IdExp(string v) : value(v) {}

// Destructor de IdExp
IdExp::~IdExp() {}

// Destructor de Stmt
Stmt::~Stmt() {}

// Crea una asignación de la expresión a la variable
AssignStmt::AssignStmt(string variable, Exp* expresion) {
    id = variable;
    e = expresion;
}

// Destructor de AssignStmt
AssignStmt::~AssignStmt() {}

// Crea una sentencia print de la expresión
PrintStmt::PrintStmt(Exp* expresion) {
    e = expresion;
}

// Destructor de PrintStmt
PrintStmt::~PrintStmt() {}

// Crea un if con su condición, rama then y rama else (puede estar vacía)
IfStmt::IfStmt(Exp* c, list<Stmt*> t, list<Stmt*> e)
    : condicion(c), thenList(t), elseList(e) {}

// Libera la condición y las sentencias de ambas ramas
IfStmt::~IfStmt() {
    delete condicion;
    for (Stmt* s : thenList) delete s;
    for (Stmt* s : elseList) delete s;
}

// Crea un while con su condición y cuerpo
WhileStmt::WhileStmt(Exp* c, list<Stmt*> b)
    : condicion(c), body(b) {}

// Libera la condición y las sentencias del cuerpo
WhileStmt::~WhileStmt() {
    delete condicion;
    for (Stmt* s : body) delete s;
}

DoWhileStmt::DoWhileStmt(Exp* c, list<Stmt*> b){
    condicion = c;
    body = b;
}

DoWhileStmt::~DoWhileStmt(){
    delete condicion;
    for (Stmt* s : body) delete s;
}

IfExp::IfExp(Exp* c, Exp* then, Exp* elsee){
    cond = c;
    thenExp = then;
    elseExp = elsee;
}

IfExp::~IfExp(){
    delete cond;
    delete thenExp;
    delete elseExp;
}

// Crea un programa vacío
Program::Program() {}

// Agrega una sentencia al final del programa
void Program::add(Stmt* a) {
    slist.push_back(a);
}

// Destructor de Program
Program::~Program() {}
