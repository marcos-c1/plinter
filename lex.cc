#include <algorithm>
#include <cctype>
#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>

#define DEBUG 0
#define MAX_NAME_LENGTH 128
#define MAX_BLOB 200.000.000 // 200MB
typedef uint8_t Byte;
std::string EXPR =
    "CREATE OR REPLACE PACKAGE pkg1 AS TYPE numset_t IS TABLE OF NUMBER;  "
    "FUNCTION f1(x NUMBER) RETURN numset_t PIPELINED; END pkg1;";

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
  CURRENT,
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

const std::unordered_map<std::string, TokenType> KEYWORD_MAPPER = {
    // Reserved words
    {"all", ALL},
    {"alter", ALTER},
    {"and", AND},
    {"any", ANY},
    {"as", AS},
    {"asc", ASC},
    {"at", AT},

    {"begin", BEGIN},
    {"between", BETWEEN},
    {"by", BY},

    {"case", CASE},
    {"check", CHECK},
    {"clusters", CLUSTERS},
    {"cluster", CLUSTER},
    {"colauth", COLAUTH},
    {"columns", COLUMNS},
    {"compress", COMPRESS},
    {"connect", CONNECT},
    {"crash", CRASH},
    {"create", CREATE},
    {"cursor", CURSOR},

    {"declare", DECLARE},
    {"default", DEFAULT},
    {"desc", DESC},
    {"distinct", DISTINCT},
    {"drop", DROP},

    {"else", ELSE},
    {"end", END},
    {"exception", EXCEPTION},
    {"exclusive", EXCLUSIVE},

    {"fetch", FETCH},
    {"for", FOR},
    {"from", FROM},
    {"function", FUNCTION},

    {"goto", GOTO},
    {"grant", GRANT},
    {"group", GROUP},

    {"having", HAVING},

    {"identified", IDENTIFIED},
    {"if", IF},
    {"in", IN},
    {"index", INDEX},
    {"indexes", INDEXES},
    {"insert", INSERT},
    {"intersect", INTERSECT},
    {"into", INTO},
    {"is", IS},

    {"like", LIKE},
    {"lock", LOCK},
    {"minus_", MINUS_},
    {"mode", MODE},

    {"nocompress", NOCOMPRESS},
    {"not", NOT},
    {"nowait", NOWAIT},
    {"null_", NULL_},
    {"of", OF},
    {"on", ON},
    {"option", OPTION},
    {"or", OR},
    {"order", ORDER},
    {"overlaps", OVERLAPS},

    {"procedure", PROCEDURE},
    {"public", PUBLIC},

    {"resource", RESOURCE},
    {"revoke", REVOKE},

    {"select", SELECT},
    {"share", SHARE},
    {"size", SIZE},
    {"sql", SQL},
    {"start", START},
    {"subtype", SUBTYPE},

    {"tabauth", TABAUTH},
    {"table", TABLE},
    {"then", THEN},
    {"to", TO},
    {"type", TYPE},

    {"union", UNION},
    {"unique", UNIQUE},
    {"update", UPDATE},

    {"values", VALUES},
    {"view", VIEW},
    {"views", VIEWS},

    {"when", WHEN},
    {"where", WHERE},
    {"with", WITH},

    // KEYWORDS
    {"add", ADD},
    {"accessible", ACCESSIBLE},
    {"agent", AGENT},
    {"aggregate", AGGREGATE},
    {"array", ARRAY},
    {"attribute", ATTRIBUTE},
    {"authid", AUTHID},
    {"avg", AVG},

    {"bfile_base", BFILE_BASE},
    {"binary", BINARY},
    {"blob_base", BLOB_BASE},
    {"block", BLOCK},
    {"body", BODY},
    {"both", BOTH},
    {"bound", BOUND},
    {"bulk", BULK},
    {"byte", BYTE},

    {"c", C},
    {"call", CALL},
    {"calling", CALLING},
    {"cascade", CASCADE},
    {"char_base", CHAR_BASE},
    {"charset", CHARSET},
    {"charsetform", CHARSETFORM},
    {"charsetid", CHARSETID},
    {"clob_base", CLOB_BASE},
    {"clone", CLONE},
    {"close", CLOSE},
    {"collect", COLLECT},
    {"comment", COMMENT},
    {"commit", COMMIT},
    {"committed", COMMITTED},
    {"compiled", COMPILED},
    {"constant", CONSTANT},
    {"constructor", CONSTRUCTOR},
    {"context", CONTEXT},
    {"continue", CONTINUE},
    {"convert", CONVERT},
    {"count", COUNT},
    {"credential", CREDENTIAL},
    {"current", CURRENT},
    {"customdatum", CUSTOMDATUM},

    {"dangling", DANGLING},
    {"data", DATA},
    {"date_base", DATE_BASE},
    {"day", DAY},
    {"define", DEFINE},
    {"delete", DELETE},
    {"deterministic", DETERMINISTIC},
    {"directory", DIRECTORY},
    {"double", DOUBLE},
    {"duration", DURATION},

    {"element", ELEMENT},
    {"elsif", ELSIF},
    {"empty", EMPTY},
    {"escape", ESCAPE},
    {"except", EXCEPT},
    {"exceptions", EXCEPTIONS},
    {"execute", EXECUTE},
    {"exists", EXISTS},
    {"exit", EXIT},
    {"external", EXTERNAL},

    {"final", FINAL},
    {"first", FIRST},
    {"fixed", FIXED},
    {"forall", FORALL},
    {"force", FORCE},

    {"general", GENERAL},

    {"hash", HASH},
    {"heap", HEAP},
    {"hidden", HIDDEN},
    {"hour", HOUR},

    {"immediate", IMMEDIATE},
    {"including", INCLUDING},
    {"indicator", INDICATOR},
    {"indices", INDICES},
    {"infinite", INFINITE},
    {"instantiable", INSTANTIABLE},
    {"interface", INTERFACE},
    {"interval", INTERVAL},
    {"invalidate", INVALIDATE},
    {"isolation", ISOLATION},

    {"java", JAVA},

    {"language", LANGUAGE},
    {"large", LARGE},
    {"leading", LEADING},
    {"length", LENGTH},
    {"level", LEVEL},
    {"library", LIBRARY},
    {"like2", LIKE2},
    {"like4", LIKE4},
    {"likec", LIKEC},
    {"limit", LIMIT},
    {"limited", LIMITED},
    {"local", LOCAL},
    {"loop", LOOP},

    {"map", MAP},
    {"max", MAX},
    {"maxlen", MAXLEN},
    {"member", MEMBER},
    {"merge", MERGE},
    {"min", MIN},
    {"minute", MINUTE},
    {"mod", MOD},
    {"modify", MODIFY},
    {"month", MONTH},
    {"multiset", MULTISET},

    {"name", NAME},
    {"nan", NAN},
    {"national", NATIONAL},
    {"native", NATIVE},
    {"nchar", NCHAR},
    {"new", NEW},
    {"nocopy", NOCOPY},
    {"number_base", NUMBER_BASE},

    {"object", OBJECT},
    {"ocicoll", OCICOLL},
    {"ocidate", OCIDATE},
    {"ocidatetime", OCIDATETIME},
    {"ociduration", OCIDURATION},
    {"ociinterval", OCIINTERVAL},
    {"ociloblocator", OCILOBLOCATOR},
    {"ocinumber", OCINUMBER},
    {"ociraw", OCIRAW},
    {"ociref", OCIREF},
    {"ocirefcursor", OCIREFCURSOR},
    {"ocirowid", OCIROWID},
    {"ocistring", OCISTRING},
    {"ocitype", OCITYPE},
    {"old", OLD},
    {"only", ONLY},
    {"opaque", OPAQUE},
    {"open", OPEN},
    {"operator", OPERATOR},
    {"oracle", ORACLE},
    {"oradata", ORADATA},
    {"organization", ORGANIZATION},
    {"orlany", ORLANY},
    {"orlvary", ORLVARY},
    {"others", OTHERS},
    {"out", OUT},
    {"overriding", OVERRIDING},

    {"package", PACKAGE},
    {"parallel_enable", PARALLEL_ENABLE},
    {"parameter", PARAMETER},
    {"parameters", PARAMETERS},
    {"parent", PARENT},
    {"partition", PARTITION},
    {"pascal", PASCAL},
    {"persistable", PERSISTABLE},
    {"pipe", PIPE},
    {"pipelined", PIPELINED},
    {"pluggable", PLUGGABLE},
    {"polymorphic", POLYMORPHIC},
    {"pragma", PRAGMA},
    {"precision", PRECISION},
    {"prior", PRIOR},
    {"private", PRIVATE},

    {"raise", RAISE},
    {"range", RANGE},
    {"read", READ},
    {"record", RECORD},
    {"ref", REF},
    {"reference", REFERENCE},
    {"relies_on", RELIES_ON},
    {"rem", REM},
    {"remainder", REMAINDER},
    {"rename", RENAME},
    {"result", RESULT},
    {"result_cache", RESULT_CACHE},
    {"return", RETURN},
    {"returning", RETURNING},
    {"reverse", REVERSE},
    {"rollback", ROLLBACK},
    {"row", ROW},

    {"sample", SAMPLE},
    {"save", SAVE},
    {"savepoint", SAVEPOINT},
    {"sb1", SB1},
    {"sb2", SB2},
    {"sb4", SB4},
    {"second", SECOND},
    {"segment", SEGMENT},
    {"self", SELF},
    {"separate", SEPARATE},
    {"sequence", SEQUENCE},
    {"serializable", SERIALIZABLE},
    {"set", SET},
    {"short", SHORT},
    {"size_t", SIZE_T},
    {"some", SOME},
    {"sparse", SPARSE},
    {"sqlcode", SQLCODE},
    {"sqldata", SQLDATA},
    {"sqlname", SQLNAME},
    {"sqlstate", SQLSTATE},
    {"standard", STANDARD},
    {"static", STATIC},
    {"stddev", STDDEV},
    {"stored", STORED},
    {"struct", STRUCT},
    {"style", STYLE},
    {"submultiset", SUBMULTISET},
    {"subpartition", SUBPARTITION},
    {"substitutable", SUBSTITUTABLE},
    {"sum", SUM},
    {"synonym", SYNONYM},

    {"tdo", TDO},
    {"the", THE},
    {"time", TIME},
    {"timezone_abbr", TIMEZONE_ABBR},
    {"timezone_hour", TIMEZONE_HOUR},
    {"timezone_minute", TIMEZONE_MINUTE},
    {"timezone_region", TIMEZONE_REGION},
    {"trailing", TRAILING},
    {"transaction", TRANSACTION},
    {"transactional", TRANSACTIONAL},
    {"trusted", TRUSTED},

    {"ub1", UB1},
    {"ub2", UB2},
    {"ub4", UB4},
    {"under", UNDER},
    {"unplug", UNPLUG},
    {"unsigned", UNSIGNED},
    {"untrusted", UNTRUSTED},
    {"use", USE},
    {"using", USING},

    {"valist", VALIST},
    {"value", VALUE},
    {"variable", VARIABLE},
    {"variance", VARIANCE},
    {"varray", VARRAY},
    {"varying", VARYING},
    {"void", VOID},

    {"while", WHILE},
    {"work", WORK},
    {"wrapped", WRAPPED},
    {"write", WRITE},

    {"year", YEAR},

    {"zone", ZONE},

    // PREDEFINED DATA TYPES (LITERALS)
    {"bfile", BFILE},
    {"blob", BLOB},
    {"boolean", BOOLEAN},
    {"char", CHAR},
    {"clob", CLOB},
    {"number", NUMBER},
    {"date", DATE},
    {"timestamp", TIMESTAMP},

    // Subtypes of NUMBER Family
    {"float", FLOAT},       // number(126)
    {"real", REAL},         // float(63)
    {"integer", INTEGER},   // number(38, 0)
    {"int", INT},           // integer
    {"smallint", SMALLINT}, // number(38, 0)
    {"decimal", DECIMAL},   // number(38, 0)
    {"numeric", NUMERIC},   // decimal
    {"dec", DEC},           // decimal
    {"binary_integer",
     BINARY_INTEGER},               // integer range  '-2147483647'..2147483647
    {"natural", NATURAL},           // binary_integer range 0..2147483647
    {"naturaln", NATURALN},         // natural not null
    {"positive", POSITIVE},         // binary_integer range 1..2147483647
    {"positiven", POSITIVEN},       // positive not null
    {"signtype", SIGNTYPE},         // binary_integer range '-1'..1
    {"pls_integer", PLS_INTEGER},   // binary_integer
    {"binary_float", BINARY_FLOAT}, // number
    {"binary_double", BINARY_DOUBLE},   // number
    {"simple_integer", SIMPLE_INTEGER}, // binary_integer not null
    {"simple_float", SIMPLE_FLOAT},     // binary_float not null
    {"simple_double", SIMPLE_DOUBLE},   // binary_double

    // Subtypes of CHAR Family
    {"varchar2", VARCHAR2},                   // char_base
    {"mlslabel", MLSLABEL},                   // char_base
    {"urowid", UROWID},                       // char_base
    {"dbms_id", DBMS_ID},                     // varchar2(128)
    {"dbms_quoted_id", DBMS_QUOTED_ID},       // varchar2(130)
    {"dbms_id_30", DBMS_ID_30},               // varchar2(30)
    {"dbms_quoted_id_30", DBMS_QUOTED_ID_30}, // varchar2(32)
    {"varchar", VARCHAR},                     // varchar2
    {"string", STRING},                       // varchar2
    {"long", LONG},                           // varchar2(32760)
    {"raw", RAW},                             // varchar2
    {"rowid", ROWID},                         // varchar2(256)
    {"character", CHARACTER},                 // char

    /* NOT TRAITING THIS SUBTYPES WITH ""
     * subtype "long raw"           is raw(32760);
     * subtype "character varying"  is varchar;
     * subtype "char varying"       is varchar;
     * subtype "national character" is char character set nchar_cs;
     * subtype "national char"      is char character set nchar_cs;
     * subtype "nchar"              is char character set nchar_cs;
     * subtype "nvarchar2"          is varchar2 character set nchar_cs;
     */

    // Subtypes of CLOB Family
    /* not traiting this subtypes with ""
     * subtype "character large object"          is clob;
     * subtype "char large object"               is clob;
     * subtype "national character large object" is clob character set nchar_cs;
     * subtype "nchar large object"              is clob character set nchar_cs;
     * subtype "nclob"                           is clob character set nchar_cs;
     */

    // Subtypes of DATE Family

    /* NOT TRAITING THIS SUBTYPES WITH ""
     * type "timestamp with time zone"       is new date_base;
     * type "interval year to month"         is new date_base;
     * type "interval day to second"         is new date_base;
     * type "timestamp with local time zone" is new date_base;
     */
    {"time_unconstrained", TIME_UNCONSTRAINED},       // time(9);
    {"time_tz_unconstrained", TIME_TZ_UNCONSTRAINED}, // time(9) with time zone;
    {"timestamp_unconstrained", TIMESTAMP_UNCONSTRAINED}, // timestamp(9);
    {"timestamp_tz_unconstrained",
     TIMESTAMP_TZ_UNCONSTRAINED}, // timestamp(9) with time zone;
    {"yminterval_unconstrained",
     YMINTERVAL_UNCONSTRAINED}, // interval year(9) to month;
    {"dsinterval_unconstrained",
     DSINTERVAL_UNCONSTRAINED}, // interval day(9) to second (9);
    {"timestamp_ltz_unconstrained",
     TIMESTAMP_LTZ_UNCONSTRAINED}, // timestamp(9) with local timezone;
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
  std::string sourceCode;
  int position;
  int row;

  Scanner(std::string sourceCode, std::list<Token> tokens, int position = 0,
          int row = 1) {
    this->tokens = tokens;
    this->sourceCode = sourceCode;
    this->position = position;
    this->row = row;
  }

  bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
  }

  bool isDigit(char c) { return (c >= '0' && c <= '9'); }

  bool isEOF() { return this->position == this->sourceCode.length(); }

  char eat() { return sourceCode.at(this->position); }

  char peek() {
    if (this->position + 1 >= sourceCode.size())
      return '\0';
    return this->sourceCode.at(this->position + 1);
  }

  void scan() {
    if (this->sourceCode.empty()) {
      fprintf(stderr, "Expression cannot be empty");
    } else {
      while (!isEOF()) {
        this->tokenizer();
      }
    }
  }

  // For now, we are looking at a constant expression. But we want to be able to
  // scan the entire file
  void tokenizer() {
    enum TokenType type = UNDEFINED;
    int col = this->position;
    char c = this->eat();

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
      if (peek() == '-') {
        while (this->sourceCode[this->position] != '\n' && !this->isEOF()) {
          this->position++;
        }
        if (this->sourceCode[this->position] == '\n')
          this->row++;

      } else {
        type = MINUS;
      }
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
      if (peek() == '*') {
        while (this->sourceCode[this->position] != '*' && !this->isEOF())
          this->position++;
        if (peek() == '/') {

        } else {
          type = UNDEFINED;
        }
      } else {
        type = SLASH;
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      this->row++;
      break;
    case '"':
      break;
    case '\'':
      while (this->sourceCode[this->position] != '\'' && !isEOF()) {
        if (this->sourceCode[this->position] == '\n')
          this->row++;
        if (this->sourceCode[this->position] != '\'')
          std::cout << this->sourceCode[this->position];
        this->position++;
      }

      if (this->isEOF()) {
        fprintf(stderr, "Unterminated string: \n");
      }

      type = STRING;
      break;
    default:
      if (isDigit(c)) {
        while (isDigit(peek())) {
          if (this->sourceCode[this->position] == '.' && isDigit(peek())) {
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
        std::string identifier =
            this->sourceCode.substr(col, this->position - col);
        std::transform(identifier.begin(), identifier.end(), identifier.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (KEYWORD_MAPPER.count(identifier)) {
          type = KEYWORD_MAPPER.at(identifier);
        } else {
          type = IDENTIFIER;
        }
      } else {
        fprintf(stderr, "Unrecognized token: %c\n", c);
        type = UNDEFINED;
      }
    }

    this->position++;

    if (type != UNDEFINED) {
      std::string lexemes = this->sourceCode.substr(col, this->position - col);
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

std::string readFile() {
  std::ifstream file("input/2.sql");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::cout << "Buffer length: " << buffer.str().length() << std::endl;
  return buffer.str();
}

int main() {
  std::list<Token> tokens;
  std::string expr = readFile();
  Scanner sc(expr, tokens);
  sc.scan();
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

// AST
