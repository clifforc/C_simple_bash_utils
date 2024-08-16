CC = gcc -Wall -Wextra -Werror
TEST_FILES = test1.txt test2.txt
PTRN = test_ptrn.txt

s21_grep : s21_grep.o
	$(CC) s21_grep.o -o s21_grep

cppcheck :
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks :
	leaks -atExit -- ./s21_grep -e ptrn1 -ie ptRN2 $(TEST_FILES)

valgrind :
	valgrind --tool=memcheck --leak-check=yes -s ./s21_grep -e ptrn1 -ie ptRN2 $(TEST_FILES)

clean :
	rm -rf s21_grep *.o

test : test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13

test1 :
	@./s21_grep ptrn1 $(TEST_FILES) > tmp_mygrep1
	@grep ptrn1 $(TEST_FILES) > tmp_orig1
	@diff tmp_mygrep1 tmp_orig1
	@rm -f tmp_mygrep1 tmp_orig1
test2 :
	@./s21_grep -e ptrn1 -ie PTRn2 $(TEST_FILES) > tmp_mygrep2
	@grep -e ptrn1 -ie PTRn2 $(TEST_FILES) > tmp_orig2
	@diff tmp_mygrep2 tmp_orig2
	@rm -f tmp_mygrep2 tmp_orig2
test3 :
	@./s21_grep -i ptRN1 $(TEST_FILES) > tmp_mygrep3
	@grep -i ptRN1 $(TEST_FILES) > tmp_orig3
	@diff tmp_mygrep3 tmp_orig3
	@rm -f tmp_mygrep3 tmp_orig3
test4 :
	@./s21_grep -v ptrn1 $(TEST_FILES) > tmp_mygrep4
	@grep -v ptrn1 $(TEST_FILES) > tmp_orig4
	@diff tmp_mygrep4 tmp_orig4
	@rm -f tmp_mygrep4 tmp_orig4
test5 :
	@./s21_grep -iv ptRN1 $(TEST_FILES) > tmp_mygrep5
	@grep -iv ptRN1 $(TEST_FILES) > tmp_orig5
	@diff tmp_mygrep5 tmp_orig5
	@rm -f tmp_mygrep5 tmp_orig5
test6 :
	@./s21_grep -in ptrn1 $(TEST_FILES) > tmp_mygrep6
	@grep -in ptrn1 $(TEST_FILES) > tmp_orig6
	@diff tmp_mygrep6 tmp_orig6
	@rm -f tmp_mygrep6 tmp_orig6
test7 :
	@./s21_grep -ince ptrn1 $(TEST_FILES) > tmp_mygrep7
	@grep -ince ptrn1 $(TEST_FILES) > tmp_orig7
	@diff tmp_mygrep7 tmp_orig7
	@rm -f tmp_mygrep7 tmp_orig7
test8 :
	@./s21_grep -lh ptrn1 $(TEST_FILES) > tmp_mygrep8
	@grep -lh ptrn1 $(TEST_FILES) > tmp_orig8
	@diff tmp_mygrep8 tmp_orig8
	@rm -f tmp_mygrep8 tmp_orig8
test9 :
	@./s21_grep -f $(PTRN) $(TEST_FILES) > tmp_mygrep9
	@grep -f $(PTRN) $(TEST_FILES) > tmp_orig9
	@diff tmp_mygrep9 tmp_orig9
	@rm -f tmp_mygrep9 tmp_orig9
test10 :
	@./s21_grep -oi ptRN1 $(TEST_FILES) > tmp_mygrep11
	@grep -oi ptRN1 $(TEST_FILES) > tmp_orig11
	@diff tmp_mygrep11 tmp_orig11
	@rm -f tmp_mygrep11 tmp_orig11
test11 :
	@./s21_grep -ohf $(PTRN) $(TEST_FILES) > tmp_mygrep12
	@grep -ohf $(PTRN) $(TEST_FILES) > tmp_orig12
	@diff tmp_mygrep12 tmp_orig12
	@rm -f tmp_mygrep12 tmp_orig12
test12 :
	@./s21_grep -oinc ptrn1 $(TEST_FILES) > tmp_mygrep13
	@grep -oinc ptrn1 $(TEST_FILES) > tmp_orig13
	@diff tmp_mygrep13 tmp_orig13
	@rm -f tmp_mygrep13 tmp_orig13
test13 :
	@./s21_grep -oihln -e ptrn1 -e ptrn2 -f $(PTRN) $(TEST_FILES) > tmp_mygrep14
	@grep -oihln -e ptrn1 -e ptrn2 -f $(PTRN) $(TEST_FILES) > tmp_orig14
	@diff tmp_mygrep14 tmp_orig14
	@rm -f tmp_mygrep14 tmp_orig14