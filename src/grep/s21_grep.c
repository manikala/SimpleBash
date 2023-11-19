#include <stdio.h>
#include <getopt.h> //для сбора параметров пришедших к нам из командной строки
//#include <stdbool.h>
#include <stdlib.h>
//#include <stddef.h> // определяет макросы нул 
//#include <unistd.h> // содержит множество полезных функций для работы с файловой системой, процессами и другими операционными системными вызовами
//#include <fcntl.h> // позволяет  выполнять  различные  команды  над  открытым файловым дескриптором fd
#include <regex.h> // регулярные выражения 
#include <string.h>

#define BUFF 10000


    typedef struct options
{

    int e; // шаблон 
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    char str_arg[BUFF]; // сюда записываем все аргументы, nтого что мы ищем 
    char str_from_file[BUFF]; // записываем сюда считанную инфу с файла 

}options; // наши опции


int parser (int argc, char* argv[], options* options);
void result (char* argv[], options* options);



int main (int argc, char* argv[]) {

    

    options my_options = {0}; // заполняем структуру флагов нулями 
    parser (argc, argv, &my_options);

    //int flag;
    //flag = parser (argc, argv, &my_options);
    //printf("%d\n", flag);

    while (optind < argc)
    {
        result (argv, &my_options);
        optind++;
    }
    
    return 0;


}



int parser (int argc, char* argv[], options* options) {

    int res = 0; 
    
    int res_count = 0;    

    //char short_options[] = "eivclnhsfo";
    char short_options[] = "e:ivclnhsf:o"; //если стоит : после е , все запишет в оптарг



    while((res = getopt_long(argc, argv, short_options, NULL, 0)) != -1) {
        switch (res) {
            case 'e': // шаблон
                options->e = 1;
                strcat(options->str_arg, optarg); // стринг билдер. Если опция принимает аргумент, то указатель на него помещается в переменную optarg
                strcat(options->str_arg, "|"); // пайпы для разделения, именно такие нужно
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
            strcat(options->str_arg, argv[optind]); // копирует второе в первое 
        }
        optind++;

    }

    // if (options->e || options->f) {
    //     options->str_arg[strlen(options->str_arg) - 1] = '\0'; // стрлен количество символов в строке. заменяем | в конце 
    // }

    if (options->e) {
        options->str_arg[strlen(options->str_arg) - 1] = '\0'; // стрлен количество символов в строке. заменяем | в конце 
    }

    // if ((argc - optind) > 0) {
        
    // }
    
    //printf("%s", options->str_arg);
    return res_count;


}

void result (char* argv[], options* options) {
    FILE *file;
    regex_t reg; //структура в которой будут храниться регулярные выражения 
    regmatch_t start;
    int coincidence = 0;
    int flag_i = REG_EXTENDED;
    if (options->i){
        flag_i = REG_EXTENDED | REG_ICASE; // икэйс убирает чувствительность к регистру . если выполнилось первое то выполнится и второе 
    }



    regcomp(&reg, options->str_arg, flag_i); // все аргументы которые мы насобирали записываем в структуру рег. а REG_EXTENDED приводит к типу регулярных выражений 
    file = fopen(argv[optind], "r");
    if (file != NULL) {
        while (fgets(options->str_from_file, BUFF, file) != NULL) // возвращает в конце нул и считывает всю строку сразу . (куда. размер строки. и от куда )
        {
            coincidence = regexec(&reg, options->str_from_file, 1, &start, 0); //сравнение рег выражений что с чем, есть ли в нашем файле эти выражения. 1 есть совпадения а 0 нет 
            if (options->v) {
                coincidence = !coincidence;
            }
            {
                /* code */
            }
            
            
            if (!coincidence) {
                printf("%s", options->str_from_file); // если было совпадение, то выводим
            }
        
        }
        fclose(file);
        
    }
    regfree(&reg);

}