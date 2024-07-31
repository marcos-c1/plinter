#include <algorithm>
#include <cctype>
#include <cstdbool>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>

#define MAX_NAME_LENGTH 128
#define MAX_BLOB 200.000.000 // 200MB
typedef uint8_t Byte;
std::string EXPR = "(6+3) - 2"; // error

enum TokenType {
  // Empty Space
  SPACE,

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

  // Reserved Words
  ALL,
  ALTER,
  AND,
  ANY,
  AS,
  ASC,
  AT,

  BEGIN,
  BETWEEN,
  BY,

  CASE,
  CHECK,
  CLUSTERS,
  CLUSTER,
  COLAUTH,
  COLUMNS,
  COMPRESS,
  CONNECT,
  CRASH,
  CREATE,
  CURSOR,

  DECLARE,
  DEFAULT,
  DESC,
  DISTINCT,
  DROP,

  ELSE,
  END,
  EXCEPTION,
  EXCLUSIVE,

  FETCH,
  FOR,
  FROM,
  FUNCTION,

  GOTO,
  GRANT,
  GROUP,

  HAVING,

  IDENTIFIED,
  IF,
  IN,
  INDEX,
  INDEXES,
  INSERT,
  INTERSECT,
  INTO,
  IS,

  LIKE,
  LOCK,
  MINUS_,
  MODE,

  NOCOMPRESS,
  NOT,
  NOWAIT,
  NULL_,
  OF,
  ON,
  OPTION,
  OR,
  ORDER,
  OVERLAPS,

  PROCEDURE,
  PUBLIC,

  RESOURCE,
  REVOKE,

  SELECT,
  SHARE,
  SIZE,
  SQL,
  START,
  SUBTYPE,

  TABAUTH,
  TABLE,
  THEN,
  TO,
  TYPE,

  UNION,
  UNIQUE,
  UPDATE,

  VALUES,
  VIEW,
  VIEWS,

  WHEN,
  WHERE,
  WITH,

  // Keywords.
  ADD,
  ACCESSIBLE,
  AGENT,
  AGGREGATE,
  ARRAY,
  ATTRIBUTE,
  AUTHID,
  AVG,

  BFILE_BASE,
  BINARY,
  BLOB_BASE,
  BLOCK,
  BODY,
  BOTH,
  BOUND,
  BULK,
  BYTE,

  C,
  CALL,
  CALLING,
  CASCADE,
  CHAR_BASE,
  CHARSET,
  CHARSETFORM,
  CHARSETID,
  CLOB_BASE,
  CLONE,
  CLOSE,
  COLLECT,
  COMMENT,
  COMMIT,
  COMMITTED,
  COMPILED,
  CONSTANT,
  CONSTRUCTOR,
  CONTEXT,
  CONTINUE,
  CONVERT,
  COUNT,
  CREDENTIAL,
  position,
  CUSTOMDATUM,

  DANGLING,
  DATA,
  DATE_BASE,
  DAY,
  DEFINE,
  DELETE,
  DETERMINISTIC,
  DIRECTORY,
  DOUBLE,
  DURATION,

  ELEMENT,
  ELSIF,
  EMPTY,
  ESCAPE,
  EXCEPT,
  EXCEPTIONS,
  EXECUTE,
  EXISTS,
  EXIT,
  EXTERNAL,

  FINAL,
  FIRST,
  FIXED,
  FORALL,
  FORCE,

  GENERAL,

  HASH,
  HEAP,
  HIDDEN,
  HOUR,

  IMMEDIATE,
  INCLUDING,
  INDICATOR,
  INDICES,
  INFINITE,
  INSTANTIABLE,
  INTERFACE,
  INTERVAL,
  INVALIDATE,
  ISOLATION,

  JAVA,

  LANGUAGE,
  LARGE,
  LEADING,
  LENGTH,
  LEVEL,
  LIBRARY,
  LIKE2,
  LIKE4,
  LIKEC,
  LIMIT,
  LIMITED,
  LOCAL,
  LOOP,

  MAP,
  MAX,
  MAXLEN,
  MEMBER,
  MERGE,
  MIN,
  MINUTE,
  MOD,
  MODIFY,
  MONTH,
  MULTISET,

  NAME,
  NAN,
  NATIONAL,
  NATIVE,
  NCHAR,
  NEW,
  NOCOPY,
  NUMBER_BASE,

  OBJECT,
  OCICOLL,
  OCIDATE,
  OCIDATETIME,
  OCIDURATION,
  OCIINTERVAL,
  OCILOBLOCATOR,
  OCINUMBER,
  OCIRAW,
  OCIREF,
  OCIREFCURSOR,
  OCIROWID,
  OCISTRING,
  OCITYPE,
  OLD,
  ONLY,
  OPAQUE,
  OPEN,
  OPERATOR,
  ORACLE,
  ORADATA,
  ORGANIZATION,
  ORLANY,
  ORLVARY,
  OTHERS,
  OUT,
  OVERRIDING,

  PACKAGE,
  PARALLEL_ENABLE,
  PARAMETER,
  PARAMETERS,
  PARENT,
  PARTITION,
  PASCAL,
  PERSISTABLE,
  PIPE,
  PIPELINED,
  PLUGGABLE,
  POLYMORPHIC,
  PRAGMA,
  PRECISION,
  PRIOR,
  PRIVATE,

  RAISE,
  RANGE,
  READ,
  RECORD,
  REF,
  REFERENCE,
  RELIES_ON,
  REM,
  REMAINDER,
  RENAME,
  RESULT,
  RESULT_CACHE,
  RETURN,
  RETURNING,
  REVERSE,
  ROLLBACK,
  ROW,

  SAMPLE,
  SAVE,
  SAVEPOINT,
  SB1,
  SB2,
  SB4,
  SECOND,
  SEGMENT,
  SELF,
  SEPARATE,
  SEQUENCE,
  SERIALIZABLE,
  SET,
  SHORT,
  SIZE_T,
  SOME,
  SPARSE,
  SQLCODE,
  SQLDATA,
  SQLNAME,
  SQLSTATE,
  STANDARD,
  STATIC,
  STDDEV,
  STORED,
  STRUCT,
  STYLE,
  SUBMULTISET,
  SUBPARTITION,
  SUBSTITUTABLE,
  SUM,
  SYNONYM,

  TDO,
  THE,
  TIME,
  TIMEZONE_ABBR,
  TIMEZONE_HOUR,
  TIMEZONE_MINUTE,
  TIMEZONE_REGION,
  TRAILING,
  TRANSACTION,
  TRANSACTIONAL,
  TRUSTED,

  UB1,
  UB2,
  UB4,
  UNDER,
  UNPLUG,
  UNSIGNED,
  UNTRUSTED,
  USE,
  USING,

  VALIST,
  VALUE,
  VARIABLE,
  VARIANCE,
  VARRAY,
  VARYING,
  VOID,

  WHILE,
  WORK,
  WRAPPED,
  WRITE,

  YEAR,

  ZONE,

  // Predefined Data Types (Literals)
  BFILE,
  BLOB,
  BOOLEAN,
  CHAR,
  CLOB,
  NUMBER,
  DATE,
  TIMESTAMP,

  // Subtypes of NUMBER Family
  FLOAT,          // NUMBER(126)
  REAL,           // FLOAT(63)
  INTEGER,        // NUMBER(38, 0)
  INT,            // INTEGER
  SMALLINT,       // NUMBER(38, 0)
  DECIMAL,        // NUMBER(38, 0)
  NUMERIC,        // DECIMAL
  DEC,            // DECIMAL
  BINARY_INTEGER, // INTEGER range  '-2147483647'..2147483647
  NATURAL,        // BINARY_INTEGER range 0..2147483647
  NATURALN,       // NATURAL not null
  POSITIVE,       // BINARY_INTEGER range 1..2147483647
  POSITIVEN,      // POSITIVE not null
  SIGNTYPE,       // BINARY_INTEGER range '-1'..1
  PLS_INTEGER,    // BINARY_INTEGER
  BINARY_FLOAT,   // NUMBER
  BINARY_DOUBLE,  // NUMBER
  SIMPLE_INTEGER, // BINARY_INTEGER NOT NULL
  SIMPLE_FLOAT,   // BINARY_FLOAT NOT NULL
  SIMPLE_DOUBLE,  // BINARY_DOUBLE

  // Subtypes of CHAR Family
  VARCHAR2,          // CHAR_BASE
  MLSLABEL,          // CHAR_BASE
  UROWID,            // CHAR_BASE
  DBMS_ID,           // VARCHAR2(128)
  DBMS_QUOTED_ID,    // VARCHAR2(130)
  DBMS_ID_30,        // VARCHAR2(30)
  DBMS_QUOTED_ID_30, // VARCHAR2(32)
  VARCHAR,           // VARCHAR2
  STRING,            // VARCHAR2
  LONG,              // VARCHAR2(32760)
  RAW,               // VARCHAR2
  ROWID,             // VARCHAR2(256)
  CHARACTER,         // CHAR
  /* NOT TRAITING THIS SUBTYPES WITH ""
   * subtype "LONG RAW"           is RAW(32760);
   * subtype "CHARACTER VARYING"  is VARCHAR;
   * subtype "CHAR VARYING"       is VARCHAR;
   * subtype "NATIONAL CHARACTER" is CHAR CHARACTER SET NCHAR_CS;
   * subtype "NATIONAL CHAR"      is CHAR CHARACTER SET NCHAR_CS;
   * subtype "NCHAR"              is CHAR CHARACTER SET NCHAR_CS;
   * subtype "NVARCHAR2"          is VARCHAR2 CHARACTER SET NCHAR_CS;
   */

  // Subtypes of CLOB Family
  /* NOT TRAITING THIS SUBTYPES WITH ""
   * subtype "CHARACTER LARGE OBJECT"          is CLOB;
   * subtype "CHAR LARGE OBJECT"               is CLOB;
   * subtype "NATIONAL CHARACTER LARGE OBJECT" is CLOB CHARACTER SET NCHAR_CS;
   * subtype "NCHAR LARGE OBJECT"              is CLOB CHARACTER SET NCHAR_CS;
   * subtype "NCLOB"                           is CLOB CHARACTER SET NCHAR_CS;*/

  // Subtypes of DATE Family
  /* NOT TRAITING THIS SUBTYPES WITH ""
   * type "TIMESTAMP WITH TIME ZONE"       is new DATE_BASE;
   * type "INTERVAL YEAR TO MONTH"         is new DATE_BASE;
   * type "INTERVAL DAY TO SECOND"         is new DATE_BASE;
   * type "TIMESTAMP WITH LOCAL TIME ZONE" is new DATE_BASE;*/
  TIME_UNCONSTRAINED,          // TIME(9);
  TIME_TZ_UNCONSTRAINED,       // TIME(9) WITH TIME ZONE;
  TIMESTAMP_UNCONSTRAINED,     // TIMESTAMP(9);
  TIMESTAMP_TZ_UNCONSTRAINED,  // TIMESTAMP(9) WITH TIME ZONE;
  YMINTERVAL_UNCONSTRAINED,    // INTERVAL YEAR(9) TO MONTH;
  DSINTERVAL_UNCONSTRAINED,    // INTERVAL DAY(9) TO SECOND (9);
  TIMESTAMP_LTZ_UNCONSTRAINED, // TIMESTAMP(9) WITH LOCAL TIME ZONE;

  // When the parser could not tokenizer
  UNDEFINED,
};

// TODO: use an hashmap to map the keyword value or an enum as subset of
// TokenType?
const std::unordered_map<std::string, TokenType> KEYWORD_MAPPER = {

};

class Token {
public:
  enum TokenType type;
  std::string lexemes;
  int row;
  int col;

  Token(enum TokenType type, std::string lexemes, int row, int col) {
    this->type = type;
    this->lexemes = lexemes;
    this->row = row;
    this->col = col;
  }
};

class Scanner {
public:
  std::list<Token> tokens;
  int position;
  int row;

  Scanner(std::list<Token> tokens, int position = 0, int row = 1) {
    this->tokens = tokens;
    this->position = position;
    this->row = row;
  }

  bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
  }

  bool isDigit(char c) { return (c >= '0' && c <= '9'); }

  bool isEOF() { return this->position == EXPR.length(); }

  char eat() { return EXPR.at(this->position); }

  char peek() {
    if (this->position + 1 >= EXPR.length())
      return '\0';
    return EXPR.at(this->position + 1);
  }

  void scan(std::string expr) {
    if (expr.empty()) {
      fprintf(stderr, "Expression cannot be empty");
    } else {
      while (!isEOF()) {
        this->tokenizer(expr);
      }
    }
  }

  // For now, we are looking at a constant expression. But we want to be able to
  // scan the entire file
  void tokenizer(std::string expr) {
    enum TokenType type;
    int col = this->position;
    char c = this->eat();

#define DEBUG 1

#if DEBUG
    std::cout << col << ' ' << c << std::endl;
#endif
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
    case '!':
      type = peek() == '=' ? BANG_EQUAL : BANG;
      break;
    case '=':
      type = peek() == '=' ? EQUAL_EQUAL : EQUAL;
      break;
    case '<':
      type = peek() == '=' ? LESS_EQUAL : LESS;
      break;
    case '>':
      type = peek() == '=' ? GREATER_EQUAL : GREATER;
      break;
    case '/':
      if (peek() == '/' || peek() == '*') {
        while (expr[this->position] != '\n' && !this->isEOF())
          this->position++;
      } else {
        type = SLASH;
      }
      break;
    case ' ':
      type = SPACE;
      break;
    case '\r':
    case '\t':
      type = UNDEFINED;
      break;
    case '\n':
      this->row++;
      break;
    case '"':
    case '\'':
      while ((expr[this->position] != '"' || expr[this->position] != '\'') &&
             !this->isEOF()) {
        if (expr[this->position] == '\n')
          this->row++;
        this->position++;
      }

      if (this->isEOF()) {
        fprintf(stderr, "Unterminated string\n");
        return;
      }

      type = STRING;
      break;
    default:
      if (isDigit(c)) {
        while (isDigit(peek())) {
          if (expr[this->position] == '.' && isDigit(peek())) {
            // Eat the .
            this->position++;
          }
          this->position++;
        }
        type = NUMBER;
      } else if (isAlpha(c)) {
        while ((isAlpha(peek()) || isDigit(peek())) && !isEOF()) {
          this->position++;
        }
        std::string identifier = expr.substr(col, this->position - col);
        std::transform(identifier.begin(), identifier.end(), identifier.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        type = IDENTIFIER;
      } else {
        fprintf(stderr, "Unrecognized token: %c\n", c);
        type = UNDEFINED;
      }
    }

    this->position++;

    if (type != UNDEFINED && type != SPACE) {
      std::string lexemes = expr.substr(col, this->position - col);
      Token tkn(type, lexemes, this->row, col);
      this->tokens.push_back(tkn);
    }
  }

  void printTokens() {
    for (Token token : this->tokens) {
      std::cout << "[" << token.row << ":" << token.col
                << "]: " << token.lexemes << std::endl;
    }
  }
};

int main() {
  std::list<Token> tokens;
  Scanner sc(tokens);
  sc.scan(EXPR);
  sc.printTokens();
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
