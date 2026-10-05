// Úkolem je vytvořit sadu funkcí, které budou pracovat se spojovými seznamy. Spojové seznamy reprezentují vojáky a implementované funkce jsou rozkazy při pořadových cvičeních.
//
// Voják v našem programu bude reprezentovaný strukturou TSOLDIER. Četa vojáků (platoon) je pak seznamem vojáků. Pro realizaci je zvolen jednosměrně zřetězený spojový seznam, kdy voják odkazuje na svého kolegu v řadě za ním.
// Poslední voják v četě má nastaven odkaz následníka na NULL. Pro reprezentaci celé čety si tak stačí pamatovat odkaz na prvého vojáka.
//
// Realizujte následující funkce (rozkazy) pro četu:
//
// TSOLDIER * mergePlatoons ( TSOLDIER *a, TSOLDIER *b );
// Funkce slouží ke sloučení dvou čet. Původní seznamy (čety) zaniknou, vojáci jsou z nich přeskupeni do nové (větší) čety sloučené. Sloučená četa je (resp. první voják v této nové četě) je pak návratovou hodnotou.
// Slučování samozřejmě není náhodné. První voják nově zformované čety bude první voják z čety a, po něm následuje první voják z čety b, druhý z a, druhý z b, atd.

// void splitPlatoon (TSOLDIER *src, TSOLDIER ** a, TSOLDIER ** b )
// Funkce slouží k rozdělení čety src na dvě menší čety. První polovina seznamu z čety src bude předaná jako výstupní parametr a, druhá polovina čety src bude předaná jako výstupní parametr b.
// Čety a a b budou tedy mít stejný počet vojáků (prvků). Pokud byl počet vojáků v původní četě lichý, bude poslední voják v seznamu odstraněn (např. odvelen jinam, ..., v programové implementaci bude zrušen a uvolněn z paměti).

// void destroyPlatoon (TSOLDIER * x );
// Funkce slouží k uvolnění paměti alokované pro vojáky v četě. Testovací prostředí tuto funkci zavolá pro každou vytvořenou četu, která již nadále není potřeba.

// struktura TSOLDIER
// Struktura popisuje jednoho vojáka. Má celkem 3 složky:
// m_Next je ukazatelem na následujícího vojáka v četě, NULL pro posledního vojáka v četě,
// m_PersonalID je číslo vojáka,
// m_SecretRecord jsou tajné osobní informace o vojákovi. Vaše funkce je nepotřebuje ani číst ani zapisovat. Jen je potřeba je zachovat v neporušeném stavu ve struktuře vojáka.

// Vstupní parametry (tedy spojové seznamy) pro Vaše funkce bude připravovat testovací prostředí. Prvky spojových seznamů budou alokované pomocí funkce malloc. Pokud některá Vaše funkce bude prvky spojového seznamu rušit, musí k uvolnění paměti použít funkci free (NEpoužívejte C++ delete).
// Funkce pro přeskupování vojáků nebudou vytvářet nové záznamy. Účelem je přeskupit stávající prvky ve spojovém seznamu tak, aby pořadí vyhovělo zadání. Váš program MUSÍ přeskupovat odkazy na další vojáky. Nepokoušejte se kopírovat obsahy struktur TSOLDIER mezi sebou.
// Kopírování obsahů struktur je jednak pomalejší a testovací prostředí je udělané tak, aby to poznalo a vyhodnotilo jako chybu.
//
// Odevzdávejte zdrojový kód, který obsahuje Vaši implementaci požadovaných funkcí. Do odevzdávaného souboru samozřejmě patří ještě další Vaše funkce, které jsou z funkce Vašich funkcí volané. Naopak, v odevzdávaném souboru nesmí být vkládání hlavičkových souborů a funkce main (pokud vkládání hlavičkových souborů a funkci main zabalíte do bloku podmíněného překladu, mohou zůstat).
//
// Úloha je omezena dobou běhu a dostupnou pamětí. Tato úloha není náročná na paměť ani na dobu běhu. Je však náročná na pečlivou práci s ukazateli. Dejte zejména pozor na ukončující hodnoty NULL na konci spojového seznamu.
// Dále, četa reprezentovaná parametrem s hodnotou NULL je platným vstupem - četou s 0 vojáky, kterou lze sloučit (nepřidá nic), rozdělit (obě nové čety budou prázdné) či zničit (uvolnění nedělá nic). Před odevzdáním si svůj program určitě zkontrolujte paměťovým debuggerem.


#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TSoldier {
    struct TSoldier *m_Next;
    int m_PersonalID;
    char m_SecretRecord[64];
} TSOLDIER;

#endif /* __PROGTEST__ */

void printList(TSOLDIER *list) {
    printf("Head");
    while (list) {
        printf(" -> %d", list->m_PersonalID);
        list = list->m_Next;
    }

    printf(" -> NULL\n");
}

int lenList(TSOLDIER *list) {
    int count = 0;

    while (list) {
        list = list->m_Next;
        count++;
    }

    return count;
}

TSOLDIER *mergePlatoons(TSOLDIER *p1, TSOLDIER *p2) {
    if (!p1) return p2;
    if (!p2) return p1;

    TSOLDIER *head = p1;
    TSOLDIER *current = p1;

    int takeP1 = 0;
    p1 = p1->m_Next;

    while (1) {
        if (!p1) {
            current->m_Next = p2;
            return head;
        }
        if (!p2) {
            current->m_Next = p1;
            return head;
        }

        if (takeP1) {
            current->m_Next = p1;
            p1 = p1->m_Next;
        } else {
            current->m_Next = p2;
            p2 = p2->m_Next;
        }

        current = current->m_Next;
        takeP1 = !takeP1;
    }
}



void splitPlatoon(TSOLDIER *src, TSOLDIER **p1, TSOLDIER **p2) {
    if (!src) {
        *p1 = NULL;
        *p2 = NULL;
        return;
    }

    TSOLDIER *tmp = src;
    int length = lenList(src);

    if (length == 1){
        free(src);
        *p1 = NULL;
        *p2 = NULL;
        return;
    }

    if (length % 2 != 0) {
        TSOLDIER *prev = NULL;
        tmp = src;
        while (tmp->m_Next) {
            prev = tmp;
            tmp = tmp->m_Next;
        }
        if (prev) {
            prev->m_Next = NULL;
        }

        free(tmp);
        length--;
    }

    int mid = length / 2;
    tmp = src;

    *p1 = src;
    TSOLDIER *prev = NULL;

    for (int i = 0; i < mid; i++) {
        prev = tmp;
        tmp = tmp->m_Next;
    }

    if (prev) {
        prev->m_Next = NULL;
    }

    *p2 = tmp;
}

void destroyPlatoon(TSOLDIER *src) {
    while (src) {
        TSOLDIER *tmp = src->m_Next;
        free(src);
        src = tmp;
    }
}

#ifndef __PROGTEST__
TSOLDIER *createSoldier(int id, TSOLDIER *next) {
    TSOLDIER *r = (TSOLDIER *) malloc(sizeof (*r));
    r->m_PersonalID = id;
    r->m_Next = next;
    /* r -> m_SecretRecord will be filled by someone with a higher security clearance */
    return r;
}

int main(void) {
    TSOLDIER *a, *b, *c;
    a = createSoldier(0,
                      createSoldier(1,
                                    createSoldier(2,
                                                  createSoldier(3,
                                                                createSoldier(4, NULL)))));
    //printList(a);
    //printf("%d\n", lenList(a));
    b = createSoldier(10,
                      createSoldier(11,
                                    createSoldier(12,
                                                  createSoldier(13,
                                                                createSoldier(14, NULL)))));
    c = mergePlatoons(a, b);
    // printList(c);
    assert(c != NULL
        && c -> m_PersonalID == 0
        && c -> m_Next != NULL
        && c -> m_Next -> m_PersonalID == 10
        && c -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_PersonalID == 1
        && c -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
        && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 3
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID
        == 14
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next ==
        NULL);
    splitPlatoon(c, &a, &b);
    // printList(a);
    // printList(b);
    assert(a != NULL
        && a -> m_PersonalID == 0
        && a -> m_Next != NULL
        && a -> m_Next -> m_PersonalID == 10
        && a -> m_Next -> m_Next != NULL
        && a -> m_Next -> m_Next -> m_PersonalID == 1
        && a -> m_Next -> m_Next -> m_Next != NULL
        && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
        && a -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
        && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL);
    assert(b != NULL
        && b -> m_PersonalID == 12
        && b -> m_Next != NULL
        && b -> m_Next -> m_PersonalID == 3
        && b -> m_Next -> m_Next != NULL
        && b -> m_Next -> m_Next -> m_PersonalID == 13
        && b -> m_Next -> m_Next -> m_Next != NULL
        && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
        && b -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
        && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL);
    destroyPlatoon(a);
    destroyPlatoon(b);

    a = createSoldier(0,
                      createSoldier(1,
                                    createSoldier(2, NULL)));
    b = createSoldier(10,
                      createSoldier(11,
                                    createSoldier(12,
                                                  createSoldier(13,
                                                                createSoldier(14, NULL)))));
    c = mergePlatoons(a, b);
    //printList(c);
    assert(c != NULL
        && c -> m_PersonalID == 0
        && c -> m_Next != NULL
        && c -> m_Next -> m_PersonalID == 10
        && c -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_PersonalID == 1
        && c -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
        && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL);
    splitPlatoon(c, &a, &b);
    //printList(a);
    //printList(b);
    assert(a != NULL
        && a -> m_PersonalID == 0
        && a -> m_Next != NULL
        && a -> m_Next -> m_PersonalID == 10
        && a -> m_Next -> m_Next != NULL
        && a -> m_Next -> m_Next -> m_PersonalID == 1
        && a -> m_Next -> m_Next -> m_Next != NULL
        && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
        && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL);
    assert(b != NULL
        && b -> m_PersonalID == 2
        && b -> m_Next != NULL
        && b -> m_Next -> m_PersonalID == 12
        && b -> m_Next -> m_Next != NULL
        && b -> m_Next -> m_Next -> m_PersonalID == 13
        && b -> m_Next -> m_Next -> m_Next != NULL
        && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
        && b -> m_Next -> m_Next -> m_Next -> m_Next == NULL);
    destroyPlatoon(a);
    destroyPlatoon(b);

    a = createSoldier(0,
                      createSoldier(1,
                                    createSoldier(2, NULL)));
    b = createSoldier(10,
                      createSoldier(11,
                                    createSoldier(12,
                                                  createSoldier(13, NULL))));
    c = mergePlatoons(a, b);
    assert(c != NULL
        && c -> m_PersonalID == 0
        && c -> m_Next != NULL
        && c -> m_Next -> m_PersonalID == 10
        && c -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_PersonalID == 1
        && c -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
        && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
        && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL);
    splitPlatoon(c, &a, &b);
    // printList(a);
    // printList(b);
    assert(a != NULL
        && a -> m_PersonalID == 0
        && a -> m_Next != NULL
        && a -> m_Next -> m_PersonalID == 10
        && a -> m_Next -> m_Next != NULL
        && a -> m_Next -> m_Next -> m_PersonalID == 1
        && a -> m_Next -> m_Next -> m_Next == NULL);
    assert(b != NULL
        && b -> m_PersonalID == 11
        && b -> m_Next != NULL
        && b -> m_Next -> m_PersonalID == 2
        && b -> m_Next -> m_Next != NULL
        && b -> m_Next -> m_Next -> m_PersonalID == 12
        && b -> m_Next -> m_Next -> m_Next == NULL);
    destroyPlatoon(a);
    destroyPlatoon(b);
    a = NULL;
    b = NULL;
    c = mergePlatoons(a,b);
    // printList(c);
    splitPlatoon(c, &a, &b);
    // printList(a);
    // printList(b);
    destroyPlatoon(a);
    destroyPlatoon(b);

    a = createSoldier(0, NULL);
    b = NULL;
    c = mergePlatoons(a, b);
    // printList(c);
    splitPlatoon(c, &a, &b);
    // printList(a);
    // printList(b);
    destroyPlatoon(a);
    destroyPlatoon(b);

    a = createSoldier(0,
                      createSoldier(1,
                                    createSoldier(2,
                                                  createSoldier(3,
                                                                createSoldier(4, NULL)))));
    b = NULL;
    c = mergePlatoons(a, b);
    // printList(c);
    splitPlatoon(c, &a, &b);
    // printList(a);
    // printList(b);
    destroyPlatoon(a);
    destroyPlatoon(b);

    return 0;
}
#endif /* __PROGTEST__ */
