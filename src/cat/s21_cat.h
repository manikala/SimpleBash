#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>  //для сбора параметров пришедших к нам из командной строки
#include <stdio.h>
//#include <stdbool.h>
#include <fcntl.h>  // позволяет  выполнять  различные  команды  над  открытым файловым дескриптором fd
// #include <stddef.h>  // определяет макросы нул
#include <stdlib.h>
#include <unistd.h>  // содержит множество полезных функций для работы с файловой системой, процессами и другими операционными системными вызовами

#define no_argument 0  // 0

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

#endif