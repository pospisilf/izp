/*
*  IZP 3. projekt
*  Filip Pospíšil
*  xpospi0f@stud.fit.vutbr.cz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int rows;
    int cols;
    unsigned char *cells[100][100];
} Map;

int field[100][100];

void help(){
    printf("Pouziti programu:\n");
    printf("./proj3 --help pro napovedu\n");
    printf("./proj3 --test soubor.txt pro kontrolu spravnosti bludiste\n");
    printf("./proj3 --rpath R C soubor.txt pro pruchod bludistem dle pravidla prave ruky se vstupem na radku R a sloupci C\n");
    printf("./proj3 --lpath R C soubor.txt pro pruchod bludistem dle pravidla leve ruky se vstupem na radku R a sloupci C\n");
    exit(0);
}

void error(int number){
    switch (number) {
        case 10:
            fprintf(stderr, "Chyba pri praci se souborem! - Otevreni\n");
            exit(1);
            break;

        case 11:
            fprintf(stderr, "Chyba pri praci se souborem! - Zavreni\n");
            exit(1);
            break;

        case 2:
            fprintf(stderr, "Neplatné hodnoty pro začátek!\n");
            exit(1);
            break;

        case 3:
            fprintf(stderr, "Pocet prvku neodpovida matici definvoane na prvnim radku!\n");
            exit(1);
            break;
        default:
            fprintf(stderr, "Blize nedefinovana chyba!\n");
            break;
    }
}

int parse(int argc , char const *argv[]) {
    if(argc == 1 || argc > 5 || !strcmp(argv[1], "--help")){ //ošetření špatného počtu argumentů, případně --help
        return 1;
    }
    else if(!strcmp(argv[1], "--test") && argc == 3){//jestli je zadaný --test i jméno souboru
        return 2;
    }
    else if(!strcmp(argv[1], "--rpath") && argc == 5){
        return 3;
    }
    else if(!strcmp(argv[1], "--lpath") && argc == 5){
        return 4;
    }
    return 1;
}

void test(){
    printf("test\n");
    exit(0);
}



int isValidInput(const char *value){
     char* p;
     errno = 0; // not 'int errno', because the '#include' already defined it
     long arg = strtol(value, &p, 10);
     if (*p != '\0' || errno != 0) {
         return -1; // In main(), returning non-zero means failure
     }
     if (arg < 0) {
         return -1;
     }
     return arg;
}

int toStruct(Map *map, const char *soubor){
    FILE * p_soubor = fopen(soubor, "r");
    if (p_soubor == NULL){
        error(10);
    }
    int numberArray[16];
    int g;
    for (g = 0; g <= 1; g++){
        fscanf(p_soubor, "%d", &numberArray[g]);
    }
    map->rows = numberArray[0];
    map->cols = numberArray[1];
    if (fclose(p_soubor) == EOF){
        error(11);
    }
    return 0;
}

void sizeTest(Map *map, const char *soubor){
    FILE * p_soubor = fopen(soubor, "r");
    if (p_soubor == NULL){
        error(10);
    }

    int numbers[map->rows*map->cols];
    int i = 0;
    numbers[0] == 0;

    for(i = -2 ; i < (map->rows*map->cols); i++) {
        int n;
        int conversion_count = fscanf(p_soubor, "%i", &n);
        if (conversion_count != 1) {
            break;
        }
        if (n == -1) {
            break;
        }
        numbers[i] = n;
    }

    if (i != map->rows*map->cols){
        error(3);
    }

    if (fclose(p_soubor) == EOF){
        error(11);
    }
}

void loadMap(Map *map, const char *soubor){
    printf("rows %d\n", map->rows);
    printf("colms %d\n", map->cols);
    printf("together %d\n", map->rows*map->cols);

    FILE * p_soubor = fopen(soubor, "r");
    if (p_soubor == NULL){
        error(10);
    }

    int numbers[map->rows*map->cols];
    int i = 0;

    int radky = 1;
    int probehlesloupce = 0;
    int nacteno = 0;
    for(i = -2 ; i < (map->rows*map->cols); i++) {
        int n;

        int conversion_count = fscanf(p_soubor, "%i", &n);

        if (nacteno<2){
            nacteno++;
        }
        else{
            if (conversion_count != 1) {
                break;
            }

            if (n == -1) {
                break;
            }

            probehlesloupce++;
            field[radky][probehlesloupce] = n;

            if(probehlesloupce == ((map->cols))){
                radky++;
                probehlesloupce = 0;
            }


        }

    }

    if (i != map->rows*map->cols){
        error(3);
    }

    if (fclose(p_soubor) == EOF){
        error(11);
    }
}

bool isborder(Map *map, int r, int c, int border){ //leva -> 1, prava -> 2, vrch/spodek = 3, vraci 0 -> neni hranice, 1-> je hranice
    int hranice = field[r][c];
    if(border == 1){
        if(hranice == 0){
            return 0; // neni hranice
        }
        else if(hranice == 1){
            return 1;
        }
        else if(hranice == 2){
            return 0;
        }
        else if(hranice == 3){
            return 1;
        }
        else if(hranice == 4){
            return 0;
        }
        else if(hranice == 5){
            return 1;
        }
        else if(hranice == 6){
            return 0;
        }
        else if(hranice == 7){
            return 1;
        }
    }
    else if(border == 2){
        if(hranice == 0){
            return 0; // neni hranice
        }
        else if(hranice == 1){
            return 0;
        }
        else if(hranice == 2){
            return 1;
        }
        else if(hranice == 3){
            return 1;
        }
        else if(hranice == 4){
            return 0;
        }
        else if(hranice == 5){
            return 0;
        }
        else if(hranice == 6){
            return 1;
        }
        else if(hranice == 7){
            return 1;
        }
    }
    else if (border == 3) {
            if(hranice == 0){
                return 0; // neni hranice
            }
            else if(hranice == 1){
                return 0;
            }
            else if(hranice == 2){
                return 0;
            }
            else if(hranice == 3){
                return 1;
            }
            else if(hranice == 4){
                return 0;
            }
            else if(hranice == 5){
                return 0;
            }
            else if(hranice == 6){
                return 1;
            }
            else if(hranice == 7){
                return 1;
            }
        }
    else{
        error(99);
    }
    return 0;
}

int lpath(Map *map, char const *argv[]){
    printf("---lpath---\n");
    return 0;
}


int rpath(Map *map, char const *argv[]){
    printf("---rpath---\n");
    toStruct(map, argv[4]); //prevedu do struktury
    sizeTest(map, argv[4]); //otestuju zda nejde o uplnou kravinu
    loadMap(map, argv[4]); //nactu mapu

    int startR = atoi(argv[2]);
    int startC = atoi(argv[3]);

    int actualR = startR;
    int actualC = startC;

    int out = 0;

    while (out == 0) {
        if (isborder(map, actualR, actualC, 1) == 1) {
            /* code */
        }
        else if (isborder(map, actualR, actualC, 2) == 1) {
            /* code */
        }
        else if (isborder(map, actualR, actualC, 3) == 1) {
            /* code */
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    Map *map, umap;
    map = &umap;
    if(parse(argc, argv) == 1) help();
    else if(parse(argc, argv) == 2) test();
    else if(parse(argc, argv) == 3) rpath(map, argv);
    else if(parse(argc, argv) == 4) lpath(map, argv);
    return 0;
}
