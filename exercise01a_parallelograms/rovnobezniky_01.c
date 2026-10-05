// Úkolem je vytvořit program, který bude počítat umístění bodů v rovině tak, aby vznikly rovnoběžníky.
//
// V rovině jsou zadané 3 body: A, B a C. Každý z bodů je zadaný pomocí svých souřadnic (dvojice desetinných čísel).
// Program tyto souřadnice přečte ze svého vstupu a určí souřadnice čtvrtého bodu tak, aby vznikl rovnoběžník (případně nějaká ze speciálních variant rovnoběžníku: kosočtverec, obdélník nebo čtverec).
// Souřadnici čtvrtého bodu program zobrazí na svém výstupu, dále zobrazí informaci o případném speciálním tvaru vznikajícího obrazce (čtverec/obdélník/ kosočtverec/rovnoběžník).
// Obecně existují 3 možnosti umístění bodu (rovnoběžníky ABA'C, ABCB' a AC'BC), viz ukázka běhu programu níže.
//
// Může se stát že vstupní body leží na přímce, pak zadání nemá žádné řešení. Program tuto situaci musí detekovat a odpovídajícím způsobem zareagovat (viz ukázka běhu programu níže).
//
// Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:
//
// nečíselné zadání souřadnic (neplatné desetinné číslo),
// chybějící souřadnice,
// chybějící nebo přebývající oddělovače (souřadnice musí být zadaná v hranatých závorkách, hodnoty x a y musí být oddělené čárkou).

// Ukázka práce programu:
// Bod A:
// [0, 0]
// Bod B:
// [7, 0]
// Bod C:
// [3, 2]
// A': [10,2], rovnobeznik
// B': [-4,2], rovnobeznik
// C': [4,-2], rovnobeznik


#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>


typedef struct
{
    double x;
    double y;
} Bod;

int read_bod(Bod *b)
{
return (scanf(" [ %lg , %lg ]", &b->x, &b->y));
}

double kolineranost(Bod A, Bod B, Bod C)
{
    double det1 = (A.x*B.y + A.y*C.x + B.x*C.y);
    double det2 = (B.y*C.x + A.x*C.y + A.y*B.x);

    return fabs(det1 - det2) < __DBL_EPSILON__ * 1e3 * (fabs(det1) + fabs(det2));
}

void caseA(Bod A, Bod B, Bod C)
{
    Bod D1;
    D1.x = B.x + (C.x - A.x);
    D1.y = B.y + (C.y - A.y);

    double AB = sqrt ( pow(B.x - A.x, 2) + pow(B.y - A.y, 2) );
    double BD1 = sqrt ( pow(D1.x - B.x, 2) + pow(D1.y - B.y, 2) );
    double AD1 = sqrt ( pow(D1.x - A.x, 2) + pow(D1.y - A.y, 2) );

    double uhol = AB*AB + BD1*BD1;

    if(((fabs (AB - BD1) < __DBL_EPSILON__ * 1e3 * (fabs (AB) + fabs (BD1)))) && (fabs (uhol - AD1*AD1) < __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AD1*AD1)))){
        printf("A': [%.7lg,%.7lg], ctverec\n", D1.x, D1.y);
    } else if ((fabs (AB - BD1) < __DBL_EPSILON__ * 1e3 * (fabs (AB) + fabs (BD1))) && (fabs (uhol - AD1*AD1) > __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AD1*AD1)))){
        printf("A': [%.7lg,%.7lg], kosoctverec\n", D1.x, D1.y);
    } else if ((fabs (AB - BD1) > __DBL_EPSILON__ * 1e3 * (fabs (AB) + fabs (BD1))) && (fabs (uhol - AD1*AD1) < __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AD1*AD1)))){
        printf("A': [%.7lg,%.7lg], obdelnik\n", D1.x, D1.y);
    } else {
        printf("A': [%.7lg,%.7lg], rovnobeznik\n", D1.x, D1.y);
    }  
} 

void caseB(Bod A, Bod B, Bod C)
{
    Bod D2;
    D2.x = A.x + (C.x - B.x);
    D2.y = A.y + (C.y - B.y);

    double AB = sqrt ( pow(B.x - A.x, 2) + pow(B.y - A.y, 2) );
    double BC = sqrt ( pow(C.x - B.x, 2) + pow(C.y - B.y, 2) );
    double AC = sqrt ( pow(C.x - A.x, 2) + pow(C.y - A.y, 2) );    

    double uhol = AB*AB + BC;


    if((fabs (AB - BC) < __DBL_EPSILON__ * 1e3 * (fabs (AB) + fabs (BC))) && (fabs (uhol - AC*AC) < __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AC*AC)))){
        printf("B': [%.7lg,%.7lg], ctverec\n", D2.x, D2.y);
    } else if ((fabs (AB - BC) < __DBL_EPSILON__ * 1e3 * (fabs (AB) + fabs (BC)) && (fabs (uhol - AC*AC)) > __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AC*AC)))){
        printf("B': [%.7lg,%.7lg], kosoctverec\n", D2.x, D2.y);
    } else if ((fabs (AB - BC) > __DBL_EPSILON__ * 1e3 * (fabs (AB) + fabs (BC))) && (fabs (uhol - AC*AC) < __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AC*AC)))){
        printf("B': [%.7lg,%.7lg], obdelnik\n", D2.x, D2.y);
    } else {
        printf("B': [%.7lg,%.7lg], rovnobeznik\n", D2.x, D2.y);
    }      
}

void caseC(Bod A, Bod B, Bod C)
{
    Bod D3;
    D3.x = B.x + (A.x - C.x);
    D3.y = B.y + (A.y - C.y);

    double AD3 = sqrt ( pow(D3.x - A.x, 2) + pow(D3.y - A.y, 2) );
    double D3B = sqrt ( pow(B.x - D3.x, 2) + pow(B.y - D3.y, 2) );
    double AB = sqrt ( pow(B.x - A.x, 2) + pow(B.y - A.y, 2) );

    double uhol = AD3*AD3 + D3B*D3B;

    if((fabs (AD3 - D3B) < __DBL_EPSILON__ * 1e3 * (fabs (AD3) + fabs (D3B))) && (fabs (uhol - AB*AB) < __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AB*AB)))){
        printf("C': [%.7lg,%.7lg], ctverec\n", D3.x, D3.y);
    } else if ((fabs (AD3 - D3B) < __DBL_EPSILON__ * 1e3 * (fabs (AD3) + fabs (D3B))) && (fabs (uhol - AB*AB) > __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AB*AB)))){
        printf("C': [%.7lg,%.7lg], kosoctverec\n", D3.x, D3.y);
    } else if ((fabs (AD3 - D3B) > __DBL_EPSILON__ * 1e3 * (fabs (AD3) + fabs (D3B))) && (fabs (uhol - AB*AB) < __DBL_EPSILON__ * 1e3 * (fabs (uhol) + fabs (AB*AB)))){
        printf("C': [%.7lg,%.7lg], obdelnik\n", D3.x, D3.y);
    } else {
        printf("C': [%.7lg,%.7lg], rovnobeznik\n", D3.x, D3.y);
    }  
}

int main(void)
{
    Bod A, B, C;

    printf("Bod A:\n");
    if (read_bod(&A) != 2)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Bod B:\n");
    if (read_bod(&B) != 2)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Bod C:\n");
    if (read_bod(&C) != 2)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    if (kolineranost(A, B, C))
    {
        printf("Rovnobezniky nelze sestrojit.\n");
        return 0;
    }

    caseA(A, B, C);
    caseB(A, B, C);
    caseC(A, B, C);

    return 0;
}
