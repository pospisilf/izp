/*
*  IZP 1. projekt
*  Filip Pospíšil
*  xpospi0f@stud.fit.vutbr.cz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX 100

char kombinace[MAX][5];
int nalezeno = 0;

char numberArray[10][5] = { //cislo predstavuje zaroven i jiste znaky abecedy
                    {'+', '\0', '\0', '\0', '\0'}, //nula
                    {'\0', '\0', '\0', '\0', '\0'}, //jednicka - radek by mohl byt vynechan, pro jednodussi zpracovani v ramci volani 2D pole jej ovsem pouzivam - abych pro ziskani hodnot napr. pod cislem 4 mohl volat numberArray[4][] a ne numberArray[3]
                    {'a', 'b', 'c', '\0', '\0'}, //dvojka
                    {'d', 'e', 'f', '\0', '\0'}, //trojka
                    {'g', 'h', 'i', '\0', '\0'}, //ctyrka
                    {'j', 'k', 'l', '\0', '\0'}, //petka
                    {'m', 'n', 'o', '\0', '\0'}, //sestka
                    {'p', 'q', 'r', 's', '\0'}, //sedmicka
                    {'t', 'u', 'v', '\0', '\0'}, //osmicka
                    {'w', 'x', 'y', 'z', '\0'} //devitka
                    };


int prirazeni(int cislo, int pozice){ //priradi do pole kombinace na pozici seznam znaku z pole numberArray
  switch(cislo){
    case 0:
      strcpy(kombinace[pozice], numberArray[0]);
      break;

    case 1:
      strcpy(kombinace[pozice], numberArray[1]);
      break;

    case 2:
      strcpy(kombinace[pozice], numberArray[2]);
      break;

    case 3:
      strcpy(kombinace[pozice], numberArray[3]);
      break;

    case 4:
      strcpy(kombinace[pozice], numberArray[4]);
      break;

    case 5:
      strcpy(kombinace[pozice], numberArray[5]);
      break;

    case 6:
      strcpy(kombinace[pozice], numberArray[6]);
      break;

    case 7:
      strcpy(kombinace[pozice], numberArray[7]);
      break;

    case 8:
      strcpy(kombinace[pozice], numberArray[8]);
    break;

    case 9:
      strcpy(kombinace[pozice], numberArray[9]);
      break;

    default:
      break;
    }

    return 0;
}

int isNumber(const char *s){ //Kontrola, zda je slozeno jen z cisel
    while (*s) { //cyklime dokud nedosahneme konce
        if (isdigit(*s++) == 0) return 0; //kontrolujeme symbol po symbolu, zda jde o cislo - jestli bude nalezen jiny znak, vracime 0
    }

    return 1; //jestli nebyl nalezen jiny znak a dosahli jsme konce retezce, vracime 1
}

void check(int value, char const *argv[]){ //Osetreni argumentu
  if (value == 1){ //jestli nebyl zadany zadny argument, tisknu stdin na stdout
  //  printf("printing input on output\n");
    int znak;
    char jmeno[MAX];
    char cislo[MAX];
    while(1){ //cyklus do nekonečna
      if(EOF != (znak = fgetc(stdin))){ //ověřím zda nenačítám znak pro EOF, zároveň ho uložím do proměnné když ne
        nalezeno = 1;
        fgets(jmeno, MAX, stdin); //načtu jméno
        fgets(cislo, MAX, stdin); //načtu číslo
        strtok(jmeno, "\n"); //převedu char na string
        strtok(cislo, "\n"); //převedu char na string
        printf("%c%s, %s\n", znak, jmeno, cislo); //tisknut output
      }
      else{ //když narazím na EOF
        if(nalezeno == 0){
          printf("Not found");
          break; //Vyskakuji z cyklu
        }
        else{
          break; //Vyskakuji z cyklu
        }
      }
    }
    exit(1);
  }
  else if(value == 2){ //Zadany jeden argument
    if (isNumber(argv[1]) == 1){ //zkontroluju, zda je celociselny
      int delka = strlen(argv[1]);
  		long givenNumber = atoi(argv[1]); //ulozim nase cislo do int givenNumber
      int obracene = 0;
      int cisloPole[MAX]; //cislo chceme v poli

      //---<vyroba arraye>---
      while (givenNumber != 0){ //cislo otocime pro jednodussi vyrobu arraye
        obracene = obracene * 10;
        obracene = obracene + givenNumber%10;
        givenNumber = givenNumber/10;
      }

      for (int i = 0; i < delka; i++) { //vyrobime si z integeru array
        cisloPole[i] = obracene%10;
        obracene = obracene/10;
      }
      //---</vyroba arraye>---

      //---<vyroba kombinaci>---
      int position = 0;
      for (int j = 0; j < delka; j++) {
        prirazeni(cisloPole[j], position);
        position++;
      }
      //---</vyroba kombinaci>---

    }
  	else{ //nebyl celociselny
  		fprintf(stderr, "Zadany argument neni slozen jen z cisla!\n"); // tisknu chybu
      exit(1); //koncim
  	}
  }
  else{ // vice argumentu
    fprintf(stderr, "Něco se pokazilo:\n-bylo zadano vice argumentu!\n");
    exit(1); //koncim
  }
}


void najdi(char const *argv[]){
  int znak;
  char jmeno[MAX];
  char jmenoTisk[MAX];
  char cislo[MAX];
  char cisloTisk[MAX];

  while(1){ //cyklus do nekonečna
    if(EOF != (znak = fgetc(stdin))){ //ověřím zda nenačítám znak pro EOF, zároveň ho uložím do proměnné když ne
      fgets(jmeno, MAX, stdin); //načtu jméno
      fgets(cislo, MAX, stdin); //načtu číslo
      strncpy(jmenoTisk, jmeno, MAX);
      strncpy(cisloTisk, cislo, MAX);
      strtok(jmenoTisk, "\n"); //převedu char na string
      strtok(cisloTisk, "\n"); //převedu char na string
      int stop = 0;
        if(strstr(cisloTisk, argv[1]) != 0){ // zkontroluju, zda nahodou neodpovida zadane cislo primo cislu
          nalezeno = 1;
         printf("%c%s, %s\n", znak, jmenoTisk, cisloTisk);
        }
        else{ //prohledávání jména
          unsigned cykly = 0;
          int radek = 0;
        //  int index = 0;
          for (size_t i = 0; (i < strlen(argv[1])) && (stop != 1); i++) {
            for (size_t j = 0; (j < 4) && (stop != 1); j++) {
              if (strchr(jmeno, kombinace[i][j]) == NULL) { //kdyz nenajdu shodu
                stop = 1; // zastav cyklus
              }
              else{ //kdyz najdu shodu
                cykly++;
                radek++;
            //    index = (strchr(jmeno, kombinace[i][j])-jmeno);
                // printf("pruchod %d radek %d index %d\n", cykly, radek, index);
              }
            }
          }
        }
    }
    else{ //když narazím na EOF
      if(nalezeno == 0){
        printf("Not found\n");
        break; //Vyskakuji z cyklu
      }
      else{
        break; //Vyskakuji z cyklu
      }
    }
  }
}

int main(const int argc, const char *argv[]){
	check(argc, argv);
  najdi(argv);
	return 0;
}


//TODO
//problém s 0 na začátku - při převádění na array vzniká problém
//při zpracování celého jména nepočítá s prvním znakem - spojit do jednoho pole
