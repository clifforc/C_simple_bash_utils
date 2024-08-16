#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Flags flag = GrepFlags(argc, argv);
  OutputFile(&flag, argc, argv);
  return 0;
}

Flags GrepFlags(int argc, char *argv[]) {
  Flags flag = {0};
  int currentFlag;
  while ((currentFlag = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (currentFlag) {
      case 'e':
        AddPattern(&flag, optarg);
        break;
      case 'i':
        flag.caseIgnore |= REG_ICASE;
        break;
      case 'v':
        flag.invertMatch = true;
        break;
      case 'c':
        flag.countMatchingLines = true;
        break;
      case 'l':
        flag.matchingFiles = true;
        break;
      case 'n':
        flag.numMatchingLines = true;
        break;
      case 'h':
        flag.matchingLines = true;
        break;
      case 's':
        flag.supressError = true;
        break;
      case 'f':
        RegexFromFile(&flag, optarg);
        break;
      case 'o':
        flag.matchingLineParts = true;
        break;
    }
  }
  if (flag.patternLen == 0) AddPattern(&flag, argv[optind++]);
  if (argc - optind == 1) flag.matchingLines = true;
  return flag;
}

void ProcessFile(Flags flag, const char *filename, regex_t *preg,
                 int numFiles) {
  FILE *file;
  if (strcmp(filename, "stdin") == 0) {
    file = stdin;
  } else {
    file = fopen(filename, "rb");
    if (file == NULL) {
      if (!flag.supressError)
        fprintf(stderr, "%s: %s\n", filename, strerror(errno));
      free(flag.pattern);
      exit(1);
    }
  }
  int countLine = 1;
  int countMatch = 0;
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, file)) != -1) {
    int result = regexec(preg, line, 0, NULL, 0);
    if ((result == 0 && !flag.invertMatch) ||
        (flag.invertMatch && result != 0)) {
      if (!flag.countMatchingLines && !flag.matchingFiles) {
        if (!flag.matchingLines && !flag.matchingLineParts &&
            strcmp(filename, "stdin") != 0)
          printf("%s:", filename);
        if (flag.numMatchingLines && !flag.matchingLineParts)
          printf("%d:", countLine);
        if (flag.matchingLineParts)
          PrintMatchingLineParts(flag, preg, line, filename, numFiles,
                                 countLine);
        else
          OutputLine(line, linelen);
      }
      countMatch++;
    }
    countLine++;
  }
  if (flag.countMatchingLines && !flag.matchingFiles) {
    if (!flag.matchingLines) printf("%s:", filename);
    printf("%d\n", countMatch);
  }
  if (flag.matchingFiles && countMatch > 0) printf("%s\n", filename);
  free(line);
  if (file != stdin) fclose(file);
}

void OutputFile(Flags *flag, int argc, char *argv[]) {
  int cflag = REG_EXTENDED;
  if (flag->caseIgnore) cflag = REG_EXTENDED | REG_ICASE;
  regex_t preg;
  int reg;
  reg = regcomp(&preg, flag->pattern, cflag);
  if (reg) {
    fprintf(stderr, "regex compile error\n");
    free(flag->pattern);
    exit(1);
  }
  if (optind == argc) {
    ProcessFile(*flag, "stdin", &preg, 1);
  } else {
    int numFiles = argc - optind;
    for (int i = optind; i < argc; i++) {
      if (access(argv[i], F_OK | R_OK) != -1) {
        ProcessFile(*flag, argv[i], &preg, numFiles);
      } else {
        if (flag->supressError) {
          fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                  argv[i]);
        }
      }
    }
  }
  regfree(&preg);
  free(flag->pattern);
}

void OutputLine(const char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void AddPattern(Flags *flag, const char *pattern) {
  if (pattern == NULL) {
    free(flag->pattern);
    fprintf(stderr, "pattern error\n");
    exit(1);
  }
  int n = strlen(pattern);
  if (flag->patternLen == 0) {
    flag->pattern = malloc(1024 * sizeof(char));
    flag->patternMem = 1024;
  }
  if (flag->patternMem < flag->patternLen + n) {
    char *temp = realloc(flag->pattern, flag->patternMem * 2);
    if (temp == NULL) {
      free(flag->pattern);
      fprintf(stderr, "memory allocation failed\n");
      exit(1);
    }
    flag->pattern = temp;
    flag->patternMem *= 2;
  }
  if (flag->patternLen != 0) {
    strcat(flag->pattern + flag->patternLen, "|");
    flag->patternLen++;
  }
  flag->patternLen +=
      sprintf(flag->pattern + flag->patternLen, "(%s)", pattern);
}

void RegexFromFile(Flags *flag, const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    if (!flag->supressError)
      fprintf(stderr, "%s: %s\n", filename, strerror(errno));
    free(flag->pattern);
    exit(1);
  }
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, file)) != -1) {
    if (line[linelen - 1] == '\n') line[linelen - 1] = '\0';
    AddPattern(flag, line);
  }
  free(line);
  fclose(file);
}

void PrintMatchingLineParts(Flags flag, regex_t *preg, char *line,
                            const char *filename, int numFiles, int countLine) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(preg, line + offset, 1, &match, 0);
    if (result != 0) break;
    if (numFiles > 1 && !flag.matchingLines) printf("%s:", filename);
    if (flag.numMatchingLines) printf("%d:", countLine);
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i + offset]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}