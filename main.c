#include <stdio.h>
#include <stdlib.h>

// Scalars
typedef enum DataType {
  BINARY_DOUBLE,
  BINARY_FLOAT,
  BINARY_INTEGER,
  DEC,
  DECIMAL,
  DOUBLE,
  FLOAT,
  INT,
  INTEGER,
  NATURAL,
  NATURALN,
  NUMBER,
  NUMERIC,
  PLS_INTEGER,
  POSITIVE,
  POSITIVEN,
  REAL,
  SIGNTYPE,
  SMALLINT,

  CHAR,
  CHARACTER,
  LONG,
  LONG_RAW,
  NCHAR,
  NVARCHAR2,
  RAW,
  ROWID,
  STRING,
  UROWID,
  VARCHAR,
  VARCHAR2,

  BOOLEAN,
  DATE
} DataType;

void *allocType(DataType t) {
  void *p;
  switch (t) {
  case BINARY_DOUBLE:
    break;
  case BINARY_FLOAT:
    break;
  case BINARY_INTEGER:
    p = malloc(sizeof(int32_t));
    break;
  case DEC:
    break;
  case DECIMAL:
    break;
  case DOUBLE:
    break;
  case FLOAT:
    break;
  case INT:
    break;
  case INTEGER:
    break;
  case NATURAL:
    break;
  case NATURALN:
    break;
  case NUMBER:
    break;
  case NUMERIC:
    break;
  case PLS_INTEGER:
    break;
  case POSITIVE:
    p = malloc(sizeof(unsigned int));
    break;
  case POSITIVEN:
    break;
  case REAL:
    break;
  case SIGNTYPE:
    p = malloc(sizeof(int8_t));
    break;
  case SMALLINT:
    break;

  case CHAR:
    break;
  case CHARACTER:
    break;
  case LONG:
    break;
  case LONG_RAW:
    break;
  case NCHAR:
    break;
  case NVARCHAR2:
    break;
  case RAW:
    break;
  case ROWID:
    break;
  case STRING:
    break;
  case UROWID:
    break;
  case VARCHAR:
    break;
  case VARCHAR2:
    break;
  case BOOLEAN:
    break;
  case DATE:
    break;
  }
}

int main() {
  printf("%ld", sizeof(char));
  return 0;
}
