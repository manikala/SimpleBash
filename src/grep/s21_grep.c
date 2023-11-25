#include "s21_grep.h"

int main(int argc, char* argv[]) {
  options my_options = {0};  // заполняем структуру флагов нулями
  parser(argc, argv, &my_options);

  // int flag;
  // flag = parser (argc, argv, &my_options);
  // printf("%d\n", flag);

  while (optind < argc) {
    result(argv, &my_options);
    optind++;
  }

  return 0;
}

int parser(int argc, char* argv[], options* options) {
  int res = 0;

  int res_count = 0;

  // char short_options[] = "eivclnhsfo";
  char short_options[] =
      "e:ivclnhsf:o";  //если стоит : после е , все запишет в оптарг

  while ((res = getopt_long(argc, argv, short_options, NULL, 0)) != -1) {
    switch (res) {
      case 'e':  // шаблон
        options->e = 1;
        strcat(options->str_arg,
               optarg);  // стринг билдер. Если опция принимает аргумент, то
                         // указатель на него помещается в переменную optarg
        strcat(options->str_arg,
               "|");  // пайпы для разделения, именно такие нужно
        res_count++;
        break;
      case 'i':
        options->i = 1;
        res_count++;
        break;
      case 'v':
        options->v = 1;
        res_count++;
        break;
      case 'c':
        options->c = 1;
        res_count++;
        break;
      case 'l':
        options->l = 1;
        res_count++;
        break;
      case 'n':
        options->n = 1;
        res_count++;
        break;
      case 'h':
        options->h = 1;
        res_count++;
        break;
      case 's':
        options->s = 1;
        res_count++;
        break;
      case 'f':
        options->f = 1;
        strcpy(options->file_name, optarg);
        flag_f(options);
        res_count++;
        break;
      case 'o':
        options->o = 1;
        res_count++;
        break;

      default:
        // fprintf(stderr, "usage - %s", short_options);
        // exit(1);
        break;
    }
    if (options->v && options->o) {
      options->o = 0;
    }
  }

  if (!options->e && !options->f) {
    if (argc > optind) {
      strcat(options->str_arg, argv[optind]);  // копирует второе в первое
    }
    optind++;
  }

  if (options->e || options->f) {
    options->str_arg[strlen(options->str_arg) - 1] =
        '\0';  // стрлен количество символов в строке. заменяем | в конце
  }

  if (argc - optind > 1) options->flag_files = 1;

  // if ((argc - optind) > 0) {

  // }

  // printf("%s", options->str_arg);
  return res_count;
}

void result(char* argv[], options* options) {
  FILE* file;
  regex_t reg;  //структура в которой будут храниться регулярные выражения
  regmatch_t start;  // нужна для старта
  // int coincidence = 0;

  int count_coincidence = 0;  // счетчмк количество совпадений флаг с
  // int count_files = 0; //флаг l
  int count_lines = 0;  // флаг n

  int flag_i = REG_EXTENDED;
  if (options->i) {
    flag_i = REG_EXTENDED |
             REG_ICASE;  // икэйс убирает чувствительность к регистру . если
                         // выполнилось первое то выполнится и второе
  }

  regcomp(
      &reg, options->str_arg,
      flag_i);  // все аргументы которые мы насобирали записываем в структуру
                // рег. а REG_EXTENDED приводит к типу регулярных выражений
  file = fopen(argv[optind], "r");
  // char names_file[1000];

  if (file != NULL) {
    while (fgets(options->str_from_file, BUFF, file) !=
           NULL)  // возвращает в конце нул и считывает всю строку сразу .
                  // (куда. размер строки. и от куда )
    {
      count_lines++;
      int coincidence = regexec(
          &reg, options->str_from_file, 1, &start,
          0);  //сравнение рег выражений что с чем, есть ли в нашем файле эти
               //выражения. 1 есть совпадения а 0 нет (совпадение)

      if (options->o) {
        strcpy(options->str_o, options->str_from_file);
      }

      if ((!coincidence || options->v) && options->flag_files && !options->l &&
          !options->h && !options->c && !options->f) {
        printf("%s:", argv[optind]);
      }

      if (!coincidence) {
        count_coincidence++;
      }

      if (options->v) {
        coincidence = !coincidence;
      }

      // if((!options->c && !options->l) && options->n && !coincidence) {
      //     printf("%d:", count_lines);
      // }

      if (!coincidence && !options->l && !options->c && !options->n &&
          !options->o) {
        printf("%s",
               options->str_from_file);  // если было совпадение, то выводим
        if (options->str_from_file[strlen(options->str_from_file) - 1] !=
            '\n') {
          printf("\n");
        }
      }

      if (!coincidence && options->n && !options->c && !options->l) {
        // printf("%s", options->str_from_file);// если было совпадение, то
        // выводим
        if (options->o) {
          printf("%d:", count_lines);
        } else {
          printf("%d:%s", count_lines, options->str_from_file);
        }
        if (options->str_from_file[strlen(options->str_from_file) - 1] !=
            '\n') {
          printf("\n");
        }
      }

      // if ((options->c || options->l) && !coincidence) {
      //     if (options->c){
      //         count_coincidence++;
      //     }
      //     if (options->l){
      //         count_files++;
      //     }
      // }
      // else if (!coincidence && !options->n && !options->o) {
      //     printf("%s", options->str_from_file); // если было совпадение, то
      //     выводим if (options->str_from_file[strlen(options->str_from_file)-
      //     1] != '\n') {
      //         printf("\n");
      //     }

      // }

      if (!coincidence && options->o && !options->l && !options->c) {  // flag o
        char* pointer = options->str_o;
        while (regexec(&reg, pointer, 1, &start, 0) == 0) {
          printf("%.*s\n", (int)(start.rm_eo - start.rm_so),
                 pointer +
                     start.rm_so);  // Каждый элемент rm_so, не равный -1,
                                    // показывает начальное смещение следующего
                                    // совпадения наибольшей подстроки внутри
                                    // заданной строки. Относительный элемент
                                    // rm_eo указывает на смещение конца
                                    // совпадения, которое является первым
                                    // символом после совпавшего текста
          pointer += start.rm_eo;
        }
      }
    }

    if (options->l && count_coincidence < 1 && options->v) {
      printf("%s\n", argv[optind]);
    }

    if (options->l && count_coincidence > 0 && !options->v) {
      // флаг л
      printf("%s\n", argv[optind]);
    }

    if (options->c && options->flag_files && !options->h) {  // flag c
      printf("%s:", argv[optind]);
    }
    if (options->c && !options->l && !options->v) {  // flag c
      printf("%d\n", count_coincidence);
    }
    if (options->c && !options->l && options->v) {
      printf("%d\n", count_lines - count_coincidence);
    }

    if (options->c && options->l) {
      if (count_coincidence > 0) {
        count_coincidence = 1;
        printf("%d\n%s\n", count_coincidence, argv[optind]);  // flag cl
      } else {
        printf("%d\n", count_coincidence);  // flag cl
      }
    }

    // if (options->l && count_files > 1 && !options->h){
    //         printf("%s\n", argv[optind]); // !!!!! нужно исправить \n
    //         последнего файла

    //     } else if (options->l && !options->h) {
    //         printf("%s", argv[optind]);
    //     }

    // if (options->c){
    //     printf("%d", count_coincidence);

    // }

    fclose(file);

  } else {
    if (!options->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    }
  }
  regfree(&reg);  // освобождает пямять для регулярных выражений
  // exit(0);
}

void flag_f(options* options) {
  FILE* file;
  file = fopen(options->file_name, "r");
  if (file != NULL) {
    if (fgets(options->str_from_file, 1000, file) != NULL) {
      if (options->str_from_file[strlen(options->str_from_file) - 1] == '\n' &&
          strlen(options->str_from_file) - 1 != 0) {
        options->str_from_file[strlen(options->str_from_file) - 1] = '\0';
      }
      strcat(options->str_arg, options->str_from_file);
      strcat(options->str_arg, "|");
    }
    fclose(file);
  }
}