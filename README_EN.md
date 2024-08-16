# Simple Bash Utils

This project implements simplified versions of the **bash** utilities `cat` and `grep` for text processing in the **C** programming language.

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![BashScript](https://img.shields.io/badge/bash-0101?style=for-the-badge&logo=gnubash&logoColor=%23FFFFFF&labelColor=%23000000)

## Description

This project involves the development of simplified versions of two command-line utilities:

1. `s21_cat` - an analog of the `cat` utility for displaying file contents.
2. `s21_grep` - an analog of the `grep` utility for searching patterns in text files.

Both utilities are developed following the principles of structured programming and support a range of command-line options.

### s21_cat

Supported options:
- `-b` (GNU: `--number-nonblank`) - numbers only non-empty lines
- `-e` - displays end-of-line characters as `$`
- `-n` (GNU: `--number`) - numbers all output lines
- `-s` (GNU: `--squeeze-blank`) - squeezes multiple adjacent empty lines
- `-t` - displays tabs as `^I`
- `-v` - displays non-printing characters

### s21_grep

Supported options:
- `-e` - pattern
- `-i` - ignores case distinctions
- `-v` - inverts the sense of matching
- `-c` - outputs only a count of matching lines
- `-l` - outputs only the names of files with matching lines
- `-n` - prefixes each line of output with the line number from the input file
- `-h` - outputs matching lines without preceding them by file names
- `-s` - suppresses error messages about nonexistent or unreadable files
- `-f` - obtains patterns from a file
- `-o` - prints only the matched (non-empty) parts of a matching line

## Building

To build the project, use the `make` command:

```
make s21_cat
make s21_grep
```

## Usage

After building, you can use the utilities as follows:

```
./s21_cat [OPTION] [FILE]...
./s21_grep [OPTION]... PATTERN [FILE]...
```

## Examples

```
./s21_cat -b text.txt
./s21_grep -v -e "pattern" file.txt
```

## License

This project is part of the educational program [School21](https://21-school.ru/) - an educational project by Sber for developers.