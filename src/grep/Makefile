CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11


all: grep

grep : s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep



clean:
	rm -rf *.o s21_grep

rebeald: clean s21_grep
	
