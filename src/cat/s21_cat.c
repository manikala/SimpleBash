#include "s21_cat.h"

#include <getopt.h>  //для сбора параметров пришедших к нам из командной строки
#include <stdio.h>
//#include <stdbool.h>
#include <fcntl.h>  // позволяет  выполнять  различные  команды  над  открытым файловым дескриптором fd
// #include <stddef.h>  // определяет макросы нул
#include <stdlib.h>
#include <unistd.h>  // содержит множество полезных функций для работы с файловой системой, процессами и другими операционными системными вызовами

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;

} options;  // наши опции

struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                {"number", no_argument, NULL, 'n'},
                                {"squeeze-blank", no_argument, NULL, 's'},
                                {NULL, no_argument, NULL, 0}

};  // данная структура поставляется вместе с самой функцией getopt_long из
    // библиотеки

int parser(int argc, char* argv[], options* options);
void reader(char* argv[], options options);

void read_consol_no_arg(int fd);
void read_file_no_arg(char* argv[]);

int main(int argc, char* argv[]) {
  options my_options = {0, 0, 0, 0,
                        0, 0, 0, 0};  // заполняем структуру флагов нулями

  int flag = parser(argc, argv, &my_options);

  // printf("\n flag = %d \n", flag);
  //  printf("\n argc = %d \n", argc);

  if (argc == 1) {  // flag == 0
    read_consol_no_arg(
        STDIN_FILENO);  // // файловый дискрипт равен 1 STDIN_FILENO

  } else if (argc == 2 && flag == 0) {  // if (argc == 2)
    read_file_no_arg(argv);

  } else {
    reader(argv, my_options);
  }

  return 1;
}

void read_consol_no_arg(int fd) {
  char
      buf[4096];  //размер страницы одной в памяти 4кб. для записи сюда из файла
  // int fd = STDIN_FILENO; // файловый дискрипт равен 1 STDIN_FILENO
  int byte_read_amount;
  byte_read_amount =
      read(fd, buf,
           4096);  // функция возращает сколько мы прочитали //пытается
                   // прочитать count байт из файлового дескриптора fd в буфер

  while (byte_read_amount != 1)  // byte_read_amount != 1 //byte_read_amount > 0
  {
    printf("%.*s", byte_read_amount,
           buf);  // эта комбинация убирает ошибку с нулем в конце строки и
                  // выводится корректно //количество символов должно быть
                  // определено переменной byte_read_amount
    byte_read_amount = read(fd, buf, 4096);
  }
}

void read_file_no_arg(char* argv[]) {
  // 3 version
  FILE* file = fopen(argv[1], "r");

  if (file) {
    int current_value;  // текущий символ

    while ((current_value = fgetc(file)) !=
           EOF) {  // fgetc – чтение одного байта из указанного потока данных
      printf("%c", current_value);
    }
    fclose(file);
  } else {
    printf("File is not found");
  }
}

int parser(int argc, char* argv[], options* options) {
  int res;  // результат этой функции будет складываться
  // int long_res; // для длинных аргементов будет складываться результат
  int res_count = 0;

  char short_options[] = "benstvTE";

  while ((res = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (res) {
      case 'b':
        options->b = 1;
        res_count++;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        res_count = res_count + 2;
        break;
      case 'E':
        options->e = 1;
        res_count++;
        break;
      case 'n':
        options->n = 1;
        res_count++;
        break;
      case 's':
        options->s = 1;
        res_count++;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        res_count = res_count + 2;
        break;
      case 'T':
        options->t = 1;
        res_count++;
        break;
      case 'v':
        options->v = 1;
        res_count++;
        break;

      default:
        fprintf(stderr, "usage - %s", short_options);
        exit(1);
    }
  }

  return res_count;
}

void reader(char* argv[], options options) {
  FILE* file = fopen(argv[optind], "r");  // optind указатель на следующий аргв

  if (file) {
    int current_value;  // текущий символ
    char prev_value = '\n';
    // char prev_prev_value = 0;
    int str_count = 0;
    int empty_count = 0;  // счетчик пустых значений
    // int count = 0;

    while ((current_value = fgetc(file)) !=
           EOF) {  // fgetc – чтение одного байта из указанного потока данных

      // 2
      if (options.s != 0 && current_value == '\n' && prev_value == '\n') {
        empty_count++;
        if (empty_count > 1) {
          continue;
        }
      } else {
        empty_count = 0;
      }
      if (((options.b != 0 && current_value != '\n') || options.n != 0) &&
          prev_value == '\n') {
        printf("%6d\t", ++str_count);
      }
      if (options.e != 0 && current_value == '\n') {
        printf("$");
      }
      if (options.t != 0 && current_value == '\t') {
        printf("^");
        current_value = 'I';
      }
      if (options.v != 0) {
        if ((current_value >= 0 && current_value < 9) ||
            (current_value > 10 && current_value < 32) ||
            (current_value > 126 && current_value <= 160)) {
          printf("^");
          if (current_value < 126) {
            current_value += 64;
          } else {
            current_value -= 64;
          }
        }
      }

      printf("%c", current_value);
      // prev_prev_value = prev_value;
      prev_value = current_value;
    }
    fclose(file);
  } else {
    printf("File is not found");
  }
}