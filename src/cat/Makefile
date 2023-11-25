CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11


all: cat

cat : s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat



clean:
	rm -rf *.o s21_cat

rebeald: clean s21_cat
	
test :
	chmod +x test_cat.sh
	./test_cat.sh
