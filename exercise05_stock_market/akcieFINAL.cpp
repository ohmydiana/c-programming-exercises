// Úkolem je realizovat program, který bude počítat zisk a ztrátu při obchodování s akciemi.
//
// Předpokládáme, že zpracováváme cenu akcie v čase. Cenu akcie se postupně dozvídáme pro jednotlivé časové okamžiky. Pro známé hodnoty ceny v minulosti chceme vypočítat maximální možný zisk a maximální možnou ztrátu.
// Při výpočtu dostaneme zadaný časový interval, ve kterém obchod proběhne. Akcii můžeme jednou nakoupit (někdy v zadaném časovém intervalu, za cenu platnou v okamžiku nákupu) a jednou prodat (opět v zadaném časovém intervalu, za cenu platnou v dobu prodeje).
// Při obchodování nelze shortovat, tj. musíme nejprve akcii nakoupit a teprve pak prodat.
//
// Vstupem programu je zadání ceny akcie prokládané dotazy na možný zisk a ztrátu. Cena akcie je zadána ve tvaru + cena, např. + 200.
// Dotaz na zisk/ztrátu má podobu ? from to, např. ? 5 10. Ceny akcie a dotazy jsou zadávané postupně, zadávání končí dosažením konce vstupu (EOF).
// Následuje ukázkový běh #1 s dodaným vysvětlením (za znakem #):
//
// + 20                 # cena v čase 0
// + 30                 # cena v čase 1
// + 40                 # cena v čase 2
// + 10                 # cena v čase 3
// ? 0 2                # hledání max. zisku/ztráty pro období <0;2>
// ? 0 3                # hledání max. zisku/ztráty pro období <0;3>
// + 50                 # cena v čase 4
// ? 0 3                # hledání max. zisku/ztráty pro období <0;3>
// ? 1 4                # hledání max. zisku/ztráty pro období <1;4>
// Výstupem programu je řešení jednotlivých zadaných problémů.
// Pro každý zadaný problém je zobrazena informace o maximálním možném zisku (spolu s časovým okamžikem nákupu a prodeje akcie) a informace o maximální možné ztrátě (opět s časovými okamžiky nákupu a prodeje).
// Pokud v zadaném intervalu nelze realizovat zisk/ztrátu, je výsledkem hodnota N/A, viz ukázka.
//
// Pokud vstup není platný, program tuto situaci detekuje, vypíše chybové hlášení a ukončí se. Formát chybového hlášení je opět uveden v ukázkách níže.
// Za chybu je považováno:
//
// nerozpoznaný vstup (nezačíná znakem + ani ?),
// neplatné zadání ceny akcie (nečíselné, záporná cena),
// neplatné zadání dotazu (neobsahuje dvě celá čísla, počátek intervalu je záporný, konec intervalu je větší nebo roven počtu dosud známých cen akcií, počátek intervalu je větší než konec intervalu).
// Pokud program detekuje chybu, přestane se dotazovat na další vstupní hodnoty, vypíše chybové hlášení a ukončí se.
// Chybu je tedy potřeba detekovat okamžitě po načtení hodnoty (neodkládejte kontrolu vstupních údajů až za načtení celého vstupu).
// Chybové hlášení vypisujte na standardní výstup (nevypisujte jej na standardní chybový výstup).
//
// Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu.
// Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování.
// Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a usnadněte si testování Vašeho programu.
//
// Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále se kontroluje i velikost použité paměti
// (k dispozici je dostatek paměti pro uložení cen akcií a dalších vypočtených hodnot; paměťové požadavky však nesmí nesmyslně překračovat rozumné meze).+ 20

// Ukázka práce programu:
// Ceny, hledani:
// + 20
// + 30
// + 40
// + 10
// ? 0 2
// Nejvyssi zisk: 20 (0 - 2)
// Nejvyssi ztrata: N/A
// ? 0 3
// Nejvyssi zisk: 20 (0 - 2)
// Nejvyssi ztrata: 30 (2 - 3)
// + 50
// ? 0 3
// Nejvyssi zisk: 20 (0 - 2)
// Nejvyssi ztrata: 30 (2 - 3)
// ? 1 4
// Nejvyssi zisk: 40 (3 - 4)
// Nejvyssi ztrata: 30 (2 - 3)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int* prices;
    size_t size, capacity;
} TSTOCKS;

int getProfitLoss(int prices[], int start, int end)
{
    int minPrice = INT_MAX, maxPrice = INT_MIN;
    int maxProfit = 0, maxLoss = 0;

    int profitStart = start, profitEnd = end;
    int lossStart = start, lossEnd = end;

    int tempProfitStart = start;
    int tempLossStart = start;

    for (int i = start; i <= end; i++)
    {
        if (prices[i] < minPrice)
        {
            minPrice = prices[i];
            tempProfitStart = i;
        }

        int profit = prices[i] - minPrice;
        if (profit > maxProfit)
        {
            maxProfit = profit;
            profitStart = tempProfitStart;
            profitEnd = i;
        }

        if (prices[i] > maxPrice)
        {
            maxPrice = prices[i];
            tempLossStart = i;
        }

        int loss = maxPrice - prices[i];
        if (loss > maxLoss)
        {
            maxLoss = loss;
            lossStart = tempLossStart;
            lossEnd = i;
        }
    }

    if (maxProfit == 0)
    {
        printf("Nejvyssi zisk: N/A\n");
    }
    else
    {
        printf("Nejvyssi zisk: %d (%d - %d)\n", maxProfit, profitStart, profitEnd);
    }

    if (maxLoss == 0)
    {
        printf("Nejvyssi ztrata: N/A\n");
        return 0;
    }
    else
    {
        printf("Nejvyssi ztrata: %d (%d - %d)\n", maxLoss, lossStart, lossEnd);
        return 1;
    }
}

int readStocks(TSTOCKS* stock, int price)
{
    if (price < 0)
    {
        return 0;
    }

    if (stock->size >= stock->capacity)
    {
        stock->capacity += stock->capacity / 2 + 10;
        stock->prices = (int*)realloc(stock->prices, stock->capacity * sizeof(int));
    }

    stock->prices[stock->size++] = price;

    return 1;
}

int processProblems(TSTOCKS* stock, int start, int end)
{
    if (start < 0 || end >= (int)stock->size || start > end)
    {
        return 0;
    }

    getProfitLoss(stock->prices, start, end);
    return 1;
}

int main(void)
{
    TSTOCKS stock = { NULL, 0, 10 };
    stock.prices = (int*)malloc(stock.capacity * sizeof(int));

    printf("Ceny, hledani:\n");

    char* line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, stdin)) != 1)
    {
        if (nread == EOF)
        {
            free(line);
            free(stock.prices);
            return 0;
        }

        char symbol, extra;
        int arg1, arg2;

        if (sscanf(line, " %c %d %d %c", &symbol, &arg1, &arg2, &extra) == 4)
        {
            printf("Nespravny vstup.\n");
            free(stock.prices);
            free(line);
            return 1;
        }
        else if (sscanf(line, " %c %d %d", &symbol, &arg1, &arg2) == 3 && symbol == '?')
        {
            if (!processProblems(&stock, arg1, arg2))
            {
                printf("Nespravny vstup.\n");
                free(stock.prices);
                free(line);
                return 1;
            }
        }
        else if (sscanf(line, " %c %d %c", &symbol, &arg1, &extra) == 3)
        {
            printf("Nespravny vstup.\n");
            free(stock.prices);
            free(line);
            return 1;
        }
        else if (sscanf(line, " %c %d", &symbol, &arg1) == 2 && symbol == '+')
        {
            if (!readStocks(&stock, arg1)) 
            {
                printf("Nespravny vstup.\n");
                free(stock.prices);
                free(line);
                return 1;
            }
        }
        else
        {
            printf("Nespravny vstup.\n");
            free(stock.prices);
            free(line);
            return 1;
        }

        free(line);
        line = NULL;
        len = 0;
    }

    free(stock.prices);
    free(line);

    return 0;
}
