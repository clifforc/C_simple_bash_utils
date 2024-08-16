#ifndef S21_CAT_H
#define S21_CAT_H

#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  bool numNonEmpty;        // -b (GNU: --number-nonblank)
  bool markEndLines;       // -e (GNU: -E without -v)
  bool numAll;             // -n (GNU: --number)
  bool squeezeBlankLines;  // -s (GNU: --squeeze-blank)
  bool dispTabs;           // -t (GNU: -T witout -v)
  bool dispNonPrintable;   // -v
} Flags;

Flags CatReadFlags(int argc, char *argv[]);
char CatDispNonPrintable(char ch);
void CatOutput(Flags flag, const char *line, int n);
void CatStream(FILE *stream, Flags flag);
void CatFile(Flags flag, int argc, char *argv[]);

#endif