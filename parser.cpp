#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "ast.h"
#include "parser.h"

using namespace std;

// Inicializa el parser leyendo el primer token
Parser::Parser(Scanner* sc) : scanner(sc) {
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        throw runtime_error("Error léxico");
    }
}

// Si el token actual es del tipo dado, avanza y devuelve true
bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

// Indica si el token actual es del tipo dado, sin avanzar
bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

// Avanza al siguiente token
bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;

        if (check(Token::ERR)) {
            throw runtime_error("Error lexico");
        }
        return true;
    }
    return false;
}

// Indica si se llegó al final de la entrada
bool Parser::isAtEnd() {
    return current->type == Token::END;
}

// Program ::= Stmt (';' Stmt)*
Program* Parser::parseProgram() {
    Program* p = new Program();
    p->add(parseStmt());
    while (match(Token::SEMICOL)) {
        p->add(parseStmt());
    }
    if (!isAtEnd()) {
        throw runtime_error("Error sintáctico");
    }

    cout << "Parseo exitoso" << endl;
    return p;
}

// StmtList ::= Stmt (';' Stmt)*
list<Stmt*> Parser::parseStmtList() {
    list<Stmt*> slist;
    slist.push_back(parseStmt());
    while (match(Token::SEMICOL)) {
        slist.push_back(parseStmt());
    }
    return slist;
}

// Stmt ::= id '=' CExp | print '(' CExp ')'
//        | if CExp then StmtList [ else StmtList ] endif
//        | while CExp do StmtList enddo
Stmt* Parser::parseStmt() {
    Exp* e;
    if (match(Token::ID)) {
        string variable = previous->text;
        match(Token::ASSIGN);
        e = parseCExp();
        return new AssignStmt(variable, e);
    }
    else if (match(Token::PRINT)) {
        match(Token::LPAREN);
        e = parseCExp();
        match(Token::RPAREN);
        return new PrintStmt(e);
    }
    else if (match(Token::IF)) {
        e = parseCExp();
        if (!match(Token::THEN)) {
            throw runtime_error("Error sintáctico: se esperaba 'then'");
        }
        list<Stmt*> thenList = parseStmtList();
        list<Stmt*> elseList;
        if (match(Token::ELSE)) {
            elseList = parseStmtList();
        }
        if (!match(Token::ENDIF)) {
            throw runtime_error("Error sintáctico: se esperaba 'endif'");
        }
        return new IfStmt(e, thenList, elseList);
    }
    else if (match(Token::WHILE)) {
        e = parseCExp();
        if (!match(Token::DO)) {
            throw runtime_error("Error sintáctico: se esperaba 'do'");
        }
        list<Stmt*> body = parseStmtList();
        if (!match(Token::ENDDO)) {
            throw runtime_error("Error sintáctico: se esperaba 'enddo'");
        }
        return new WhileStmt(e, body);
    }
    else {
        throw runtime_error("Error sintáctico");
    }
}

// CExp ::= BExp [ <= BExp ]
Exp* Parser::parseCExp() {
    Exp* l = parseBExp();
    if (match(Token::LE)) {
        Exp* r = parseBExp();
        l = new BinaryExp(l, r, LE_OP);
    }
    return l;
}

// BExp ::= expr { (+ | -) expr }*
Exp* Parser::parseBExp() {
    Exp* l = parseExpr();
    while (match(Token::PLUS) || match(Token::MINUS)) {
        BinaryOp op;
        if (previous->type == Token::PLUS) {
            op = PLUS_OP;
        }
        else {
            op = MINUS_OP;
        }
        Exp* r = parseExpr();
        l = new BinaryExp(l, r, op);
    }
    return l;
}

// expr ::= term { (* | /) term }*
Exp* Parser::parseExpr() {
    Exp* l = parseTerm();
    while (match(Token::MUL) || match(Token::DIV)) {
        BinaryOp op;
        if (previous->type == Token::MUL) {
            op = MUL_OP;
        }
        else {
            op = DIV_OP;
        }
        Exp* r = parseTerm();
        l = new BinaryExp(l, r, op);
    }
    return l;
}

// term ::= factor [ ** factor ]
Exp* Parser::parseTerm() {
    Exp* l = parseFactor();
    if (match(Token::POW)) {
        Exp* r = parseFactor();
        l = new BinaryExp(l, r, POW_OP);
    }
    return l;
}

// factor ::= number | '(' CExp ')' | id
Exp* Parser::parseFactor() {
    if (match(Token::NUM)) {
        return new NumberExp(stoi(previous->text));
    }
    else if (match(Token::LPAREN)) {
        Exp* e = parseCExp();
        match(Token::RPAREN);
        return e;
    }
    else if (match(Token::ID)) {
        return new IdExp(previous->text);
    }
    else {
        throw runtime_error("Error sintáctico");
    }
}
