#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flag = CatReadFlags(argc, argv);
  if (optind == argc) {
    CatStream(stdin, flag);
  } else {
    CatFile(flag, argc, argv);
  }
  return 0;
}

Flags CatReadFlags(int argc, char *argv[]) {
  struct option longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {0, 0, 0, 0}};
  Flags flag = {false, false, false, false, false, false};
  while (optind < argc) {
    if (argv[optind][0] != '-') {
      break;
    }
    int currentFlag;
    if ((currentFlag =
             getopt_long(argc, argv, "beEnstTv", longOptions, NULL)) == -1) {
      break;
    }
    switch (currentFlag) {
      case 'b':
        flag.numNonEmpty = true;
        break;
      case 'e':
        flag.markEndLines = true;
        flag.dispNonPrintable = true;
        break;
      case 'E':
        flag.markEndLines = true;
        break;
      case 'n':
        flag.numAll = true;
        break;
      case 's':
        flag.squeezeBlankLines = true;
        break;
      case 't':
        flag.dispTabs = true;
        flag.dispNonPrintable = true;
        break;
      case 'T':
        flag.dispTabs = true;
        break;
      case 'v':
        flag.dispNonPrintable = true;
        break;
      default:
        printf("usage: %s [-beEnstTv] [file ...]", argv[0]);
        exit(1);
        break;
    }
  }
  return flag;
}

char CatDispNonPrintable(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch < 0) {
    putchar('M');
    putchar('-');
    ch = ch & 0b01111111;
  }
  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void CatOutput(Flags flag, const char *line, int n) {
  for (int i = 0; i < n; i++) {
    char tempChar = line[i];
    if (flag.markEndLines && tempChar == '\n') {
      putchar('$');
    }
    if (flag.dispTabs && tempChar == '\t') {
      putchar('^');
      putchar('I');
      continue;
    }
    if (flag.dispNonPrintable) {
      tempChar = CatDispNonPrintable(tempChar);
    }
    putchar(tempChar);
  }
}

void CatStream(FILE *stream, Flags flag) {
  int countLine = 0;
  bool squeeze = false;

  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while ((linelen = getline(&line, &linecap, stream)) != -1) {
    if (flag.squeezeBlankLines && line[0] == '\n') {
      if (squeeze) continue;
      squeeze = true;
    } else {
      squeeze = false;
    }
    if (flag.numNonEmpty) {
      if (line[0] != '\n') {
        printf("%6d\t", ++countLine);
      }
    } else if (flag.numAll) {
      printf("%6d\t", ++countLine);
    }
    CatOutput(flag, line, linelen);
  }
  free(line);
}

void CatFile(Flags flag, int argc, char *argv[]) {
  for (char **fileName = &argv[optind], **end = &argv[argc]; fileName != end;
       ++fileName) {
    errno = 0;
    FILE *file = fopen(*fileName, "rb");
    if (file == NULL) {
      fprintf(stderr, "%s: %s: %s\n", argv[0], *fileName, strerror(errno));
      continue;
    }
    CatStream(file, flag);
    fclose(file);
  }
}