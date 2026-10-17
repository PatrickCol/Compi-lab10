#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "ast.h"

// Parser descendente recursivo: consume tokens del scanner y construye el AST
class Parser {
private:
    Scanner* scanner;
    Token *current, *previous;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    bool advance();
    bool isAtEnd();

public:
    Parser(Scanner* scanner);
    Program* parseProgram();
    Stmt* parseStmt();
    list<Stmt*> parseStmtList();
    Exp* parseCExp();
    Exp* parseBExp();
    Exp* parseExpr();
    Exp* parseTerm();
    Exp* parseFactor();
};

#endif // PARSER_H
