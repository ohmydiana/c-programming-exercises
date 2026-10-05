// Úkolem je realizovat funkce (ne celý program, pouze funkce), které budou analyzovat zápisy zadaného čísla v různých číselných soustavách.
//
// Uvažujme celé kladné číslo věší nebo rovné 2. Takové číslo lze zapsat v různých číselných soustavách, v každé soustavě může mít zápis čísla jinou podobu.
// Úkolem funkcí je nalézt takový zápis zadaného čísla, který:
//
// končí co nejdelší posloupností nul (primární kritérium) a
// základ číselné soustavy je co největší (pomocné kritérium).
// Například číslo 21610 lze zapsat v různých číselných soustavách jako: 21610, 110110002, 220003, 31204, 13315, 10006, 4267, 3308, ..., d816, 6036, ..., 10216.
// Z těchto zápisů nás zajímají zápisy 110110002, 220003 a 10006, protože končí na 3 nuly (toto je nejvyšší počet nul, kterého lze pro číslo 216 dosáhnout, první kritérium).
// Následně uplatníme druhé pravidlo (co nejvyšší základ), tedy hledaným zápisem bude 10006 - číslo končí trojicí nul a je zapsáno v šestkové soustavě.
//
// long long findRadix ( long long x )
// funkce dostane parametrem číslo x. Nalezne základ číselné soustavy, ve které zápis čísla x končí co nejvíce nulami. Pokud takových základů existuje více, vrátí funkce největší takový základ.
// Pokud je parametr neplatný (číslo x je menší než 2), vrátí funkce hodnotu -1.

// int countZeros ( long long x )
// funkce dostane parametrem číslo x. Nalezne základ číselné soustavy, ve které zápis čísla x končí co nejvíce nulami a vrátí tento počet. Pokud je parametr neplatný (číslo x je menší než 2), vrátí funkce hodnotu -1.

// bool findRadixZeros ( long long x, long long * radix, int * zeros )
// funkce dostane parametrem číslo x. Nalezne základ číselné soustavy, ve které zápis čísla x končí co nejvíce nulami. Pokud takových základů existuje více, nalezne funkce největší takový základ.
// Dále funkce určí počet nul, kterými zápis čísla x v nalezené soustavě končí. Nalezený základ soustavy a počet nul funkce uloží do výstupních parametrů radix a zeros.
// Návratovou hodnotou funkce je hodnota true (platný parametr x, vyplněné výstupní parametry) nebo false (číslo x je menší než 2, výstupní parametry nejsou vyplněné).

// Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Rozumná implementace naivního algoritmu by měla projít všemi testy kromě testů rychlosti. Pro zvládnutí testů rychlosti je potřeba použít výkonnější algoritmus.


#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#endif /* __PROGTEST__ */

int counting_zeros(long long x, long long base)
{
  int count = 0;
  
  while(x % base == 0)
  {
    x /= base;
    count++;
  }

  return count;
}

long long findRadix      ( long long   x )
{
  if(x < 2) return -1;

  long long biggestRadix = 2;
  int maxZeros = 0;

  for(int base = 2; base <= x; base++)
  {
    int zeros = counting_zeros(x, base);

    if(zeros > maxZeros)
    {
      maxZeros = zeros;
      biggestRadix = base;
    } 
    else if (zeros == maxZeros && base > biggestRadix)
    {
        biggestRadix = base;
    }
  }
  
  return biggestRadix;
}

int       countZeros     ( long long   x )
{
  if(x < 2) return -1;

  int maxZeros = 0;

  for(int base = 2; base <= x; base++)
  {
    int zeros = counting_zeros(x, base);

    if(zeros > maxZeros)
    {
      maxZeros = zeros;
    }
  }

  return maxZeros;
}

bool      findRadixZeros ( long long   x,
                           long long * radix,
                           int       * zeros )
{
  if(x < 2) return false;

  long long biggestRadix = 2;
  int maxZeros = 0;

  for(int base = 2; base <= x; base++)
  {
    int currentZeros = counting_zeros(x, base);

    if(currentZeros > maxZeros)
    {
      maxZeros = currentZeros;
      biggestRadix = base;
    } else if (currentZeros == maxZeros && base > biggestRadix)
    {
        biggestRadix = base;
    }
  }

  *radix = biggestRadix;
  *zeros = maxZeros;

  return true;
}

#ifndef __PROGTEST__
int       main ()
{
  long long radix;
  int       zeros;
  assert ( findRadix ( 2 ) == 2 );
  assert ( countZeros ( 2 ) == 1 );
  assert ( findRadixZeros ( 2, &radix, &zeros )
           && radix == 2
           && zeros == 1 );
  assert ( findRadix ( 16 ) == 2 );
  assert ( countZeros ( 16 ) == 4 );
  assert ( findRadixZeros ( 16, &radix, &zeros )
           && radix == 2
           && zeros == 4 );
  assert ( findRadix ( 17 ) == 17 );
  assert ( countZeros ( 17 ) == 1 );
  assert ( findRadixZeros ( 17, &radix, &zeros )
           && radix == 17
           && zeros == 1 );
  assert ( findRadix ( 36 ) == 6 );
  assert ( countZeros ( 36 ) == 2 );
  assert ( findRadixZeros ( 36, &radix, &zeros )
           && radix == 6
           && zeros == 2 );
  assert ( findRadix ( 100 ) == 10 );
  assert ( countZeros ( 100 ) == 2 );
  assert ( findRadixZeros ( 100, &radix, &zeros )
           && radix == 10
           && zeros == 2 );
  assert ( findRadix ( 216 ) == 6 );
  assert ( countZeros ( 216 ) == 3 );
  assert ( findRadixZeros ( 216, &radix, &zeros )
           && radix == 6
           && zeros == 3 );
  assert ( findRadix ( 343 ) == 7 );
  assert ( countZeros ( 343 ) == 3 );
  assert ( findRadixZeros ( 343, &radix, &zeros )
           && radix == 7
           && zeros == 3 );
  assert ( findRadix ( 1024 ) == 2 );
  assert ( countZeros ( 1024 ) == 10 );
  assert ( findRadixZeros ( 1024, &radix, &zeros )
           && radix == 2
           && zeros == 10 );
  assert ( findRadix ( 1296 ) == 6 );
  assert ( countZeros ( 1296 ) == 4 );
  assert ( findRadixZeros ( 1296, &radix, &zeros )
           && radix == 6
           && zeros == 4 );
  assert ( findRadix ( -8 ) == -1 );
  assert ( countZeros ( -8 ) == -1 );
  assert ( ! findRadixZeros ( -8, &radix, &zeros ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
