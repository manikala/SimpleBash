#ifndef S21_GREP_H
#define S21_GREP_H

#define BUFF 10000

#include <getopt.h>  //для сбора параметров пришедших к нам из командной строки
#include <stdio.h>
//#include <stdbool.h>
#include <stdlib.h>
//#include <stddef.h> // определяет макросы нул
//#include <unistd.h> // содержит множество полезных функций для работы с
//файловой системой, процессами и другими операционными системными вызовами
//#include <fcntl.h> // позволяет  выполнять  различные  команды  над  открытым
//файловым дескриптором fd
#include <regex.h>  // регулярные выражения
#include <string.h>

typedef struct options {
  int e;  // шаблон
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int flag_files;      // если файлов больше 1 то = 1
  char str_arg[BUFF];  // сюда записываем все аргументы, nтого что мы ищем
  char str_from_file[BUFF];  // записываем сюда считанную инфу с файла

  char str_o[BUFF];  // строка шаблонов для o
  char file_name[BUFF];

} options;  // наши опции

void parser(int argc, char* argv[], options* options);
void result(char* argv[], options* options);
void flag_f(options* options);

#endif