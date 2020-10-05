/*
*  IZP 2. projekt
*  Filip Pospíšil
*  xpospi0f@stud.fit.vutbr.cz
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define i0 1e-12 //konstanta
#define ut 0.0258563 //konstanta


/*
Funkce na výpis erroru na stderr.
Vstup: -
Výstup: -
*/
void error(){
    fprintf(stderr, "error: invalid arguments\n");
    exit(1);
}


/*
Funkce na kontrolu argumentů.
Vstup: argumenty
Výstup: -/Error
*/
void arg_check(int argc , char const *argv[]){
    if(argc == 4){
        if(strtod(argv[1], NULL)<0||strtod(argv[2], NULL)<0||strtod(argv[3], NULL)<=0){
            error();
        }
    }
    else{
        error();
        exit(1);
    }
}


/*
Funkce na mezivýpočet během výpočtu UP
Vstup: UP - "domnělá" hodnota, U0 - vstupní napětí, R - odpor.
Výstup: hodnota UP.
*/
// double up_temp(double up, double u0, double r){
//     return u0 - (i0*(exp(up/ut)-1) * r);
// }
double up_temp(double up, double u0, double r){
    return u0 - (i0*((exp(up/ut)-1)) * r);
         //u0 -  Ir * R
}


/*
Funkce na proudu v diodě pomocí Shockleyho rovnice
Vstup: UP - Napětí na diodě.
Výstup: IP - proud na diodě.
*/
double shockley(double up){
    return i0*(exp(up/ut)-1);

}


/*
Funkce na výpočet UP.
Vstup: U0 - vstupní napětí, EPS - odchylka, R - odpor.
Výstup: UP - napětí na diodě.
*/
double upCount(double u0, double eps, double r){
    double start = 0;
    double middle = (start+u0)/2;
    double fmid = up_temp(middle, u0, r);
    while (fabs(fmid) > eps){
        if (up_temp(start, u0, r) * fmid < 0){
            u0 = middle;
        }
        else{
            start = middle;
        }
        if (fabs(fmid) > eps){
            middle = (start+u0)/2;
            fmid = up_temp(middle, u0, r);
        }
    }
    return middle;
}


/*
Funkce na výpis UP a IP.
Vstup: U0 - vstupní napětí, R - odpor, EPS - odchylka.
Výstup: hodnoty UP a IP na stdout.
*/
double diode(double u0, double r, double eps){
        double upFinal = upCount(u0, eps, r);
        printf("up=%g V\n", upFinal);
        printf("ip=%g A\n", shockley(upFinal));
        return 0;
};



int main(int argc, char const *argv[]) {
    arg_check(argc, argv);
    diode(strtod(argv[1], NULL), strtod(argv[2], NULL), strtod(argv[3], NULL));
    return 0;
}


//TODO: Kontrola argumentů, ošetření inf a NaN stavů.
//TODO: Zpřesnění výpočtů!
