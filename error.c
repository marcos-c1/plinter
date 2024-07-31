#include <stdio.h>

/*
 * params:
 *  int level (0, 1, 2), which respective are the output stream (stdin,
 * stdout, stderr
 *  const char* msg: The message that will display to the user
 */
static void error(FILE *level, const char *msg) {
  fprintf(level, "[%s, %d] %s\n", __TIME__, __LINE__, msg);
}
