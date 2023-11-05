#include "s21_cat.h"

#include <stdio.h>
#include <getopt.h> //для сбора параметров пришедших к нам из командной строки
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h> // определяет макросы нул 

    typedef struct options
{

    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int E;
    int T;

}options; // наши опции

    struct option long_options[] = { 
        {"number-nonblank", no_argument, NULL, 'b'},
        //{"show-ends", 0, NULL, 'e'},
        //{"show-ends", 0, NULL, 'E'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {NULL, no_argument, NULL, 0}
        // {"show-tabs", 0, NULL, 't'},
        // {"show-tabs", 0, NULL, 'T'},
        // {"show-nonprinting", 0, NULL, 'v'},
    }; // данная структура поставляется вместе с самой функцией getopt_long из библиотеки

void parser (int argc, char* argv[], options* options);
void reader (char* argv[], options options);



int main (int argc, char* argv[]) {
    
    options my_options = {0, 0, 0, 0, 0, 0, 0, 0}; // заполняем структуру флагов нулями 

    parser (argc, argv, &my_options);
    if (my_options.b != 0) {
        my_options.n = 0; 
    }
    reader (argv, my_options);     

}

void parser (int argc, char* argv[], options *options) {
    
    int res; // результат этой функции будет складываться
    int long_res; // для длинных аргементов будет складываться результат
    int res_count = 0;

    char short_options[] = "benstvTE";



    while((res = getopt_long(argc, argv, short_options, long_options, &long_res)) != -1) {
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
}

void reader (char* argv[], options options){

    FILE *file = fopen(argv[optind], "R"); // optind указатель на следующий аргв

    if (file) {

        int current_value; // текущий символ
        int str_count = 0;
        int empty_count= 0; // счетчик пустых значений
        int count = 0;

        while ((current_value = fgetc(file)) != EOF ) { // fgetc – чтение одного байта из указанного потока данных

            if (options.b != 0) {
                if (current_value != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (options.e != 0) {
                if (current_value != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (options.n != 0) {
                if (current_value != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (options.s != 0) {
                if (current_value != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (options.t != 0) {
                if (current_value != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (options.v != 0) {
                if (current_value != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
        }

    } else {
        printf("File is not found");
    }

}
