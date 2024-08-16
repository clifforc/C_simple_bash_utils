#ifndef S21_GREP_H
#define S21_GREP_H

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Flags {
  int caseIgnore;           //  -i Ignore uppercase vs. lowercase.
  bool invertMatch;         //  -v
  bool countMatchingLines;  //  -c Output count of matching lines only.
  bool matchingFiles;       //  -l Output matching files only.
  bool numMatchingLines;   //  -n Precede each matching line with a line number.
  bool matchingLines;      //  -h Output matching lines
  bool supressError;       //  -s Suppress error messages
  bool matchingLineParts;  // -o Output matched parts of matching line.
  char *pattern;
  int patternLen;
  int patternMem;
} Flags;

void AddPattern(Flags *flag, const char *pattern);
void RegexFromFile(Flags *flag, const char *filename);
Flags GrepFlags(int argc, char *argv[]);
void PrintMatchingLineParts(Flags flag, regex_t *preg, char *line,
                            const char *filename, int numFiles, int countLine);
void OutputLine(const char *line, int n);
void ProcessFile(Flags flag, const char *filename, regex_t *preg, int numFiles);
void OutputFile(Flags *flag, int argc, char *argv[]);

#endif