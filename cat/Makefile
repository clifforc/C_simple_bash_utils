CC = gcc -Wall -Wextra -Werror
TEST_FILES = table.txt

s21_cat : s21_cat.o
	$(CC) s21_cat.o -o s21_cat

cppcheck :
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks :
	leaks -atExit -- ./s21_cat -en $(TEST_FILES)

valgrind :
	valgrind --tool=memcheck --leak-check=yes -s ./s21_cat -en $(TEST_FILES)

clean :
	rm -rf s21_cat *.o

test : test1 test2 test3 test4 test5 test6 test7 test8 test9

test1 :
	@./s21_cat -e $(TEST_FILES) > tmp_mycat1
	@cat -ev $(TEST_FILES) > tmp_orig1
	@diff tmp_mycat1 tmp_orig1
	@rm -f tmp_mycat1 tmp_orig1

test2 :
	@./s21_cat -b $(TEST_FILES) > tmp_mycat2
	@cat -b $(TEST_FILES) > tmp_orig2
	@diff tmp_mycat2 tmp_orig2
	@rm -f tmp_mycat2 tmp_orig2

test3 :
	@./s21_cat -n $(TEST_FILES) > tmp_mycat3
	@cat -n $(TEST_FILES) > tmp_orig3
	@diff tmp_mycat3 tmp_orig3
	@rm -f tmp_mycat3 tmp_orig3

test4 :
	@./s21_cat -s $(TEST_FILES) > tmp_mycat4
	@cat -s $(TEST_FILES) > tmp_orig4
	@diff tmp_mycat4 tmp_orig4
	@rm -f tmp_mycat4 tmp_orig4

test5 :
	@./s21_cat -t $(TEST_FILES) > tmp_mycat5
	@cat -tv $(TEST_FILES) > tmp_orig5
	@diff tmp_mycat5 tmp_orig5
	@rm -f tmp_mycat5 tmp_orig5

test6 :
	@./s21_cat -v $(TEST_FILES) > tmp_mycat6
	@cat -v $(TEST_FILES) > tmp_orig6
	@diff tmp_mycat6 tmp_orig6
	@rm -f tmp_mycat6 tmp_orig6

test7 :
	@./s21_cat --number-nonblank $(TEST_FILES) > tmp_mycat7
	@cat -b $(TEST_FILES) > tmp_orig7
	@diff tmp_mycat7 tmp_orig7
	@rm -f tmp_mycat7 tmp_orig7

test8 :
	@./s21_cat --number $(TEST_FILES) > tmp_mycat8
	@cat -n $(TEST_FILES) > tmp_orig8
	@diff tmp_mycat8 tmp_orig8
	@rm -f tmp_mycat8 tmp_orig8

test9 :
	@./s21_cat -bestv test1.txt > tmp_mycat9
	@cat -bestv test1.txt > tmp_orig9
	@diff tmp_mycat9 tmp_orig9
	@rm -f tmp_mycat9 tmp_orig9