
#ifdef S21_CAT.H
#define S21_CAT.H
#include <stdio.h>
#include <getopt.h> //для сбора параметров пришедших к нам из командной строки
#include <stdbool.h>
//#include <unistd.h>


#define no_argument         0   //0
#define required_argument   1   //1
#define optional_argument   2   //2

    typedef struct 
{

    int b
    int e
    int n
    int s
    int t
    int v

}options; // наши опции

void parser (int argc, char* argv[], flags *flag);





#endif