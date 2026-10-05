// Úkolem je realizovat funkci (ne celý program, pouze funkci), která nahradí v textu arabská čísla jejich římskými ekvivalenty.
//
// Předpokládáme řetězec, který obsahuje text. Text je tvořen slovy, čísly, bílými znaky a interpunkcí. V zadaném textu chceme všechna arabská čísla nahradit jejich římskými ekvivalenty:
//
// nahrazujeme pouze čísla v uzavřeném intervalu 1 až 3999 (arabská čísla mimo tento interval necháváme bez změny),
// nahrazujeme pouze čísla, která jsou od zbytku textu oddělena oddělovači (bílé znaky, interpunkce). Například čísla v textech abc123, abc123def nebo 123abc nejsou oddělena, proto je nebudeme nahrazovat,
// záporná čísla a desetinná čísla neuvažujeme. Např. v zápisu -123 nebo 123.456 čísla nahradíme, protože znak mínus a tečku považujeme za oddělovače,
// římská čísla zapisujeme pomocí znaků velké abecedy.
// Požadovaná funkce má rozhraní:
//
// char * arabicToRoman ( const char * text )
// Parametr text odkazuje na řetězec, ve kterém máme čísla nahradit. Text z parametru nebude funkce měnit (je const). Funkce si dynamicky alokuje prostor pro nový řetězec a do něj umístí upravený text s nahrazenými čísly.
// Návratovou hodnotou je ukazatel na takto alokovaný řetězec. Za uvolnění předaného řetězce je zodpovědný volající (zavolá na něj funkci free, viz přiložené ukázky).

#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#endif  /* __PROGTEST__ */

void numberToRoman (long int num, char* strConverted)
{
  const int numArabic[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

  const char* numRoman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

  strConverted[0] = 0;
  size_t offset = 0;

  for(int i = 0; i < 13 && num > 0; i++)
  {
    while (num >= numArabic[i])
    {
      int lenRoman = strlen(numRoman[i]);
      memcpy(strConverted + offset, numRoman[i], lenRoman);
      offset += lenRoman;
      num -= numArabic[i];
    }

    strConverted[offset] = '\0';
  }
}

int isSepataror (char c)
{
  if(isspace(c) || ispunct(c))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

char * arabicToRoman ( const char * str )
{
  size_t len = strlen(str);
  char* result = (char*)malloc(len * 15 + 1);
  result[0] = 0;

  long int number;
  char temporary[20];

  size_t resultIndex = 0;
  size_t i = 0;
  
  result[0] = '\0';


  while (i < len)
  {
    if (isdigit(str[i]) && 
        (i == 0 || isSepataror(str[i - 1])) && 
        (i + 1 == len || isSepataror(str[i + 1]) || isdigit(str[i + 1])))
    {
      char* endptr;
      number = strtol(&str[i], &endptr, 10);

      if (number >= 1 && number <= 3999)
      {
        temporary[0] = 0;
        numberToRoman(number, temporary);

        int lenRoman = strlen(temporary);
        memcpy(result + resultIndex, temporary, lenRoman);
        resultIndex += lenRoman;

        i += endptr - &str[i];
        continue;
      }
    }

    result[resultIndex++] = str[i++];
  }

  result[resultIndex] = '\0';
  return result;
  
}

#ifndef __PROGTEST__
int main ()
{
  char * r;

  r = arabicToRoman ( "CVUT FIT was founded on July 1-st 2009" );
  assert ( ! strcmp ( r, "CVUT FIT was founded on July I-st MMIX" ) );
  free ( r );

  r = arabicToRoman ( "PA1 is my favorite subject, rating 5 out of 5stars" );
  assert ( ! strcmp ( r, "PA1 is my favorite subject, rating V out of 5stars" ) );
  free ( r );

  r = arabicToRoman ( "The range of int data type is -2147483648 to 2147483647 inclusive." );
  assert ( ! strcmp ( r, "The range of int data type is -2147483648 to 2147483647 inclusive." ) );
  free ( r );

  r = arabicToRoman ( "There are 11 integers in closed interval 10-20" );
  assert ( ! strcmp ( r, "There are XI integers in closed interval X-XX" ) );
  free ( r );

  r = arabicToRoman ( "Chuck Norris and agent 007 are able to solve all Progtest homework problems on the 1-st try" );
  assert ( ! strcmp ( r, "Chuck Norris and agent VII are able to solve all Progtest homework problems on the I-st try" ) );
  free ( r );

  return EXIT_SUCCESS;
}
#endif  /* __PROGTEST__ */
