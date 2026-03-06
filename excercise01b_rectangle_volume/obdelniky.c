// Úkolem je realizovat program, který bude rozhodovat o obsahu zadaných obdélníků.
//
// Předpokládáme, že v rovině jsou dva obdélníky, každý je určen svoji výškou a šířkou. Výška a šířka jsou desetinná čísla větší než 0.
//
// Program dostane na vstupu 4 čísla, tato reprezentují výšku a šířku prvního obdélníku a výšku a šířku druhého obdélníku.
//
// Výstupem programu je rozhodnutí, zda mají zadané obdélníky stejný obsah. Výstupem je odpověď, který z obdélníků má menší obsah,
// případně informace o shodném obsahu. Přesný formát odpovědi je vidět v ukázkách.
//
// Pokud vstup není platný (na vstupu jsou nečíselné nebo nesmyslné hodnoty), program tuto situaci detekuje a vypíše chybové hlášení.
// Formát chybového hlášení je opět uveden v ukázkách níže. Za chybu je považováno, pokud je na vstupu:
//
// nečíselná hodnota nebo
// nesmyslná hodnota (záporná hodnota, nula, zadání chybí).
// Pokud program detekuje chybu, přestane se dotazovat na další vstupní hodnoty, vypíše chybové hlášení a ukončí se.
// Chybu je tedy potřeba detekovat okamžitě po načtení hodnoty (neodkládejte kontrolu vstupních údajů až za načtení celého vstupu).
// Chybové hlášení vypisujte na standardní výstup (nevypisujte jej na standardní chybový výstup).
//
// Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu.
// Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování.
// Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a usnadněte si testování Vašeho programu.
//
// Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít problém).

// Ukázka práce programu:

// Obdelnik #1:
// 7.5 12
// Obdelnik #2:
// 6 15
// Obdelniky maji stejny obsah.

// Obdelnik #1:
// 22 18
// Obdelnik #2:
// 13 9
// Obdelnik #2 ma mensi obsah.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double x1, y1, x2, y2;
    double S1, S2;

    printf("Obdelnik #1:\n");
    if (scanf("%lf %lf", &x1, &x2) != 2 || x1 <= 0 || x2 <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }


    
    printf("Obdelnik #2:\n");
    if (scanf("%lf %lf", &y1, &y2) != 2 || y1 <= 0 || y2 <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    S1 = x1 * x2;
    S2 = y1 * y2;

    if (fabs (S1 - S2) < __DBL_EPSILON__ * 1e3 * (fabs (S1) + fabs (S2)))
    {
        printf("Obdelniky maji stejny obsah.\n");
    } else if (S1 < S2) {
        printf("Obdelnik #1 ma mensi obsah.\n");
    } else {
        printf("Obdelnik #2 ma mensi obsah.\n");
    }

    return 0;
}
