#ifndef AST_H
#define AST_H

#include <string>
#include <unordered_map>
#include <list>
#include <ostream>

using namespace std;

class Visitor;

// Operadores binarios del lenguaje
enum BinaryOp {
    PLUS_OP,
    MINUS_OP,
    MUL_OP,
    DIV_OP,
    POW_OP,
    LE_OP
};

// Clase base abstracta de todas las expresiones
class Exp {
public:
    virtual int accept(Visitor* visitor) = 0;
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
};

// Expresión binaria: left op right
class BinaryExp : public Exp {
public:
    Exp* left;
    Exp* right;
    BinaryOp op;
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    int accept(Visitor* visitor);
    ~BinaryExp();
};

// Expresión numérica: un literal entero
class NumberExp : public Exp {
public:
    int value;
    NumberExp(int v);
    int accept(Visitor* visitor);
    ~NumberExp();
};

// Expresión identificador: uso de una variable
class IdExp : public Exp {
public:
    string value;
    IdExp(string v);
    int accept(Visitor* visitor);
    ~IdExp();
};

// Clase base abstracta de todas las sentencias
class Stmt {
public:
    virtual int accept(Visitor* visitor) = 0;
    virtual ~Stmt() = 0;
};

// Sentencia de asignación: id = e
class AssignStmt : public Stmt {
public:
    string id;
    Exp* e;
    AssignStmt(string, Exp*);
    int accept(Visitor* visitor);
    ~AssignStmt();
};

// Sentencia de impresión: print(e)
class PrintStmt : public Stmt {
public:
    Exp* e;
    PrintStmt(Exp*);
    int accept(Visitor* visitor);
    ~PrintStmt();
};

// Sentencia condicional: if CExp then StmtList [else StmtList] endif
class IfStmt : public Stmt {
public:
    Exp* condicion;
    list<Stmt*> thenList;
    list<Stmt*> elseList;
    IfStmt(Exp*, list<Stmt*>, list<Stmt*>);
    int accept(Visitor* visitor);
    ~IfStmt();
};

// Sentencia de repetición: while CExp do StmtList enddo
class WhileStmt : public Stmt {
public:
    Exp* condicion;
    list<Stmt*> body;
    WhileStmt(Exp*, list<Stmt*>);
    int accept(Visitor* visitor);
    ~WhileStmt();
};

class BreakStmt : public Stmt {
public:
    BreakStmt(){};
    int accept(Visitor* visitor);
    ~BreakStmt(){};
};

// Sentencia de repeticion: do StmtList while CExp
class DoWhileStmt : public Stmt {
public:
    Exp* condicion;
    list<Stmt*> body;
    DoWhileStmt(Exp*, list<Stmt*>);
    int accept(Visitor* visitor);
    ~DoWhileStmt();
};

// Expresion condicional: ifexp (CExp, CExp, CExp)
class IfExp : public Exp {
public:
    Exp* cond, *thenExp, *elseExp;
    IfExp(Exp*, Exp*, Exp*);
    int accept(Visitor* visitor);
    ~IfExp();
};

// Programa: lista de sentencias
class Program {
public:
    list<Stmt*> slist;
    Program();
    void add(Stmt*);
    ~Program();
};

#endif // AST_H
