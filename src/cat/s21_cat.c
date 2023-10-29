#include "s21_cat.h"






int main (int argc, char* argv[]) {



    

    options my_options = {0}; // заполняем структуру флагов нулями 

    parser (argc, argv, &my_options);

     
}


void parser (int argc, char* argv[], flags *flag) {
    
    int res; // результат этой функции будет складываться
    int long_res; // для длинных аргементов будет складываться результат

    char short_options[] = "benstvTE";

    static struct option long_options[] = { 
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'}
    }; // данная структура поставляется вместе с самой функцией getopt_long из библиотеки

    getopt_long(argc, argv, short_options, long_options)


}

