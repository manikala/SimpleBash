#include "s21_cat.h"

#include <stdio.h>
#include <getopt.h> //для сбора параметров пришедших к нам из командной строки
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h> // определяет макросы нул 
#include <unistd.h> // содержит множество полезных функций для работы с файловой системой, процессами и другими операционными системными вызовами
#include <fcntl.h> // позволяет  выполнять  различные  команды  над  открытым файловым дескриптором fd

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

int parser (int argc, char* argv[], options* options);
void reader (char* argv[], options options);

void read_consol_no_arg (int fd);
void read_file_no_arg (char* argv[]);




int main (int argc, char* argv[]) {
    
    options my_options = {0, 0, 0, 0, 0, 0, 0, 0}; // заполняем структуру флагов нулями 

    int flag = parser (argc, argv, &my_options);
    
    //printf("\n flag = %d \n", flag);
    // printf("\n argc = %d \n", argc);
    
    

    if (argc == 1) { //flag == 0
        read_consol_no_arg (STDIN_FILENO);        

    } else if (argc == 2 && flag == 0){//if (argc == 2)
        read_file_no_arg (argv);
        
    } else {
        reader (argv, my_options);
    } 


    
    // else {
    //     if (my_options.b != 0) {
    //     my_options.n = 0; 
    // }
    // reader (argv, my_options);   

    // }


      
    return 1;
}


void read_consol_no_arg (int fd) {
    char buf[4096]; //размер страницы одной в памяти 4кб. для записи сюда из файла 
    //int fd = STDIN_FILENO; // файловый дискрипт равен 1 STDIN_FILENO
    int byte_read_amount;
    byte_read_amount = read(fd, buf, 4096); // функция возращает сколько мы прочитали 

    while (byte_read_amount != 1) // byte_read_amount != 1 //byte_read_amount > 0
    {
        printf("%.*s", byte_read_amount, buf); // эта комбинация убирает ошибку с нулем в конце строки и выводится корректно 
        byte_read_amount = read(fd, buf, 4096);
    }

}


void read_file_no_arg (char* argv[]) {
    //(void)argc;
    int fd = open(argv[1], O_RDONLY); // функция открывает файл. O_RDONLY - значит что мы будем только читать из файла
    //read_consol_no_arg (open(argv[1], O_RDONLY));

    char buf[4096]; //размер страницы одной в памяти 4кб. для записи сюда из файла 
    //int fd = STDIN_FILENO; // файловый дискрипт равен 1 STDIN_FILENO
    int byte_read_amount;
    byte_read_amount = read(fd, buf, 4096); // функция возращает сколько мы прочитали 

    while (byte_read_amount > 0) // byte_read_amount != 1 //byte_read_amount > 0
    {
        printf("%.*s", byte_read_amount, buf); // эта комбинация убирает ошибку с нулем в конце строки и выводится корректно 
        byte_read_amount = read(fd, buf, 4096);
    }





    // FILE *file = fopen(argv[1], "r"); // optind указатель на следующий аргв

    // if (file) {

    //     int current_value; // текущий символ


    //     while ((current_value = fgetc(file)) != EOF ) { // fgetc – чтение одного байта из указанного потока данных
    //         printf("%d", current_value);

    //     }
    //     fclose(file);
    // } else {
    //     printf("File is not found");
    // }

}









int parser (int argc, char* argv[], options *options) {
    
    int res; // результат этой функции будет складываться
    //int long_res; // для длинных аргементов будет складываться результат
    int res_count = 0;    

    char short_options[] = "benstvTE";



    while((res = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
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


void reader (char* argv[], options options){

    FILE *file = fopen(argv[optind], "r"); // optind указатель на следующий аргв

    if (file) {

        int current_value; // текущий символ
        char prev_value = '\n';
        char prev_prev_value = 0;
        int str_count = 0;
        //int empty_count= 0; // счетчик пустых значений
        //int count = 0;

        while ((current_value = fgetc(file)) != EOF ) { // fgetc – чтение одного байта из указанного потока данных

            if (options.b != 0) {
                if (current_value != '\n' && prev_value == '\n'){
                    //if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        //count = 1;
                    //} else {
                        //count = 0;
                    //}
                }    
            }
            if ((options.e != 0 && options.v != 0) || options.E != 0) {
                if (current_value == '\n'){
                    printf("$");
                }    
            }
            if (options.n != 0 && options.b == 0) {
                if (prev_value == '\n'){
                    //if (count == 0) {
                        printf ("%6d\t", ++str_count);
                        //count = 1;
                    //} else {
                        //count = 0;
                    //}
                }    
            }
            if (options.s != 0) {
                if (current_value == '\n' && prev_value == '\n' && prev_prev_value == '\n'){
                    //if (count == 0) {
                        //printf ("\n");
                        //count = 1;

                    //} else {
                        //count = 0;
                    //}
                    continue;
                } 
                // else if (current_value != '\n' && prev_value == '\n') {
                //     printf("%c", prev_value);
                //     prev_value = current_value;
                //     continue;
                // }  
            }
            if ((options.t != 0 && options.v != 0) || options.E != 0)  {
                if (current_value == '\t'){
                    //if (count == 0) {
                        printf ("^");
                        current_value ='I';
                        //count = 1;
                    //} else {
                        //count = 0;
                    //}
                }    
            }
            // if (options.v != 0) {
            //     if (current_value != '\n'){
            //         if (count == 0) {
            //             printf ("%6d\t", ++str_count);
            //             count = 1;
            //         } else {
            //             count = 0;
            //         }
            //     }    
            // }

            
            printf("%c", current_value);
            prev_prev_value = prev_value;
            prev_value = current_value;




        }
        fclose(file);
    } else {
        printf("File is not found");
    }

}