#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const char *String;
typedef uint8_t Byte;

const char *EXPR = "6+2/2\0";

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  EOF_ = EOF
};

typedef struct Token {
  enum TokenType type;
  String lexemes;
  void *literal;
  int line;
} Token;

typedef struct Object {

} Object;

typedef struct Node {
  Token *data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  size_t size;
  Node *root;
} List;

typedef struct Scanner {
  Token *tokens;
  int start;
  int current;
  int line;
} Scanner;

Node *initNode(Token *data) {
  Node *n = malloc(sizeof(Node));
  n->data = data;
  n->next = NULL;
  return n;
}

List *initList() {
  List *l = malloc(sizeof(List));
  l->root = NULL;
  l->size = 0;
  return l;
}

void appendNode(List *l, Token *data) {
  Node *node = initNode(data);
  if (l->root == NULL) {
    l->root = node;
  } else {
    Node *aux = l->root;
    while (aux->next) {
      aux = aux->next;
    }
    aux->next = node;
  }
  l->size++;
}

Scanner *initScanner() {
  Scanner *sc = malloc(sizeof(Scanner));
  sc->start = 0;
  sc->current = 0;
  sc->line = 0;
  return sc;
}

Token initToken(enum TokenType type, String lexemes, void *literal, int line) {
  Token tkn;
  tkn.type = type;
  tkn.lexemes = lexemes;
  tkn.literal = literal;
  tkn.line = line;
  return tkn;
}

Token tokenizer(Scanner *sc, String expr) {
  enum TokenType type;
  char c = expr[sc->current++];
  switch (c) {
  case '(':
    type = LEFT_PAREN;
    break;
  case ')':
    type = RIGHT_PAREN;
    break;
  case '{':
    type = LEFT_BRACE;
    break;
  case '}':
    type = RIGHT_BRACE;
    break;
  case ',':
    type = COMMA;
    break;
  case '.':
    type = DOT;
    break;
  case '-':
    type = MINUS;
    break;
  case '+':
    type = PLUS;
    break;
  case ';':
    type = SEMICOLON;
    break;
  case '*':
    type = STAR;
    break;
  default:
    fprintf(stderr, "Unrecognized token: %s", c);
    break;
  }
  char *lexemes;
  strncpy(lexemes, expr, sc->current - sc->start);
  Token tkn = initToken(type, lexemes, NULL, sc->line);
  return tkn;
}

// For now, we are looking at a constant expression. But we want to be able to
// scan the entire file
bool isEOF(Scanner *sc) { return sc->current == strlen(EXPR); }

void evaluate(List *tokens, Scanner *sc, String expr) {
  while (!isEOF(sc)) {
    Token tkn = tokenizer(sc, expr);
    appendNode(tokens, (void *)&tkn);
  }
}

void scanning(String expr) {
  Scanner *sc = initScanner();
  List *tokens;

  if (strlen(expr) == 0) {
    fprintf(stderr, "Expression cannot be empty");
  } else {
    evaluate(tokens, sc, expr);
  }

  free(sc);
  free(tokens);
}

/* ------------------------------------------------------------------------
 *  PRECEDENCE RULE
 *
 * Precedence determines which operator is evaluated first in an expression
 * containing a mixture of different operators. Precedence * rules tell us
 * that we evaluate the / before the - in the above example. Operators with
 * higher precedence are evaluated before ope* rators with lower precedence.
 * Equivalently, higher precedence operators are said to “bind tighter”.
 * ------------------------------------------------------------------------
 *  */
/* ------------------------------------------------------------------------
 * ASSOCIATIVITY RULE
 *
 * Associativity determines which operator is evaluated first in a series of
 * the same operator. When an operator is left-associative (think
 * “left-to-right”), operators on the left evaluate before those on the
 * right. Since - is left-associative
 * ------------------------------------------------------------------------
 */

// void binaryOP(left, op, right);

/* RECURSIVE DESCENT PARSING
 * A top-down parser because it starts from the top or outermost grammar
 * rule and works its way down int the nested subexpressions before finally
 * reaching the leaves of the syntax tree.
 *
 *    |----------------------|
 *    |  EQUALITY            |       lower precedence
 *    |  COMPARISON          |
 *    |  ADITION             |            to
 *    |  MULTIPLICATION      |
 *    |  UNARY               |        high precedence
 *    |----------------------|
 *
 */
