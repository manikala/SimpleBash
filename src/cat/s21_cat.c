#include "s21_cat.h"

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

int main (int argc, char* argv[]) {
    
    options my_options = {0}; // заполняем структуру флагов нулями 

    parser (argc, argv, &my_options);
    if (my_options -> b) {
        my_options -> n = 0 
    }
    reader (argv, *my_options);     
}

void parser (int argc, char* argv[], options *options) {
    
    int res; // результат этой функции будет складываться
    int long_res; // для длинных аргементов будет складываться результат
    int res_count = 0;

    char short_options[] = "benstvTE";

    static struct option long_options[] = { 
        {"number-nonblank", no_argument, NULL, 'b'},
        //{"show-ends", 0, NULL, 'e'},
        //{"show-ends", 0, NULL, 'E'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'}
        // {"show-tabs", 0, NULL, 't'},
        // {"show-tabs", 0, NULL, 'T'},
        // {"show-nonprinting", 0, NULL, 'v'},
    }; // данная структура поставляется вместе с самой функцией getopt_long из библиотеки

    while((res = getopt_long(argc, argv, short_options, long_options, &long_res)) != -1) {
        switch (opt) {
            case 'b':
                my_options -> b = 1;
                res_count++;
                break;
            case 'e':
                my_options -> e = 1;
                my_options -> v = 1;
                res_count = res_count + 2;
                break;
            case 'E':
                my_options -> e = 1;
                res_count++;
                break;
            case 'n':
                my_options -> n = 1;
                res_count++;
                break;
            case 's':
                my_options -> s = 1;
                res_count++;
                break;
            case 't':
                my_options -> t = 1;
                my_options -> v = 1;
                res_count = res_count + 2;                
                break;
            case 'T':
                my_options -> t = 1;
                res_count++;
                break;
            case 'v':
                my_options -> v = 1;
                res_count++;
                break;

            default:
                fprintf(stderr, "usage - %s", short_options);
                exit(1);
            
        }
    }
}

void reader (char* argv[], options *options){

    File *file = fopen(argv[optind], "R"); // optind указатель на следующий аргв

    if (file) {

        int current_value; // текущий символ
        int str_count = 0;
        int empty_count= 0; // счетчик пустых значений
        int count = 0;

        while ((current_value = fgets(file)) != EOF ) {

            if (my_options -> b) {
                if (cur != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (my_options -> e) {
                if (cur != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (my_options -> n) {
                if (cur != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (my_options -> s) {
                if (cur != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (my_options -> t) {
                if (cur != '\n'){
                    if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        count = 1;
                    } else {
                        count = 0;
                    }
                }    
            }
            if (my_options -> v) {
                if (cur != '\n'){
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
