// Úkolem je realizovat funkci (ne celý program, pouze funkci), bude porovnávat výsledky ve hře poker.
//
// Funkce má následující rozhraní:
//
// int comparePokerHands ( const int a[], const int b[] );
// vstupními parametry funkce jsou dvě pole playerA a playerB. Každé pole obsahuje 5 prvků - karet, které drží hráč A a B. Obě tato pole jsou určena pouze ke čtení,
// návratovou hodnotou funkce je hodnota porovnání karet:
// RES_WIN_A - vyhrává hráč A,
// RES_WIN_B - vyhrává hráč B,
// RES_DRAW - oba hráči mají stejně hodnocené karty,
// RES_INVALID - karty jsou neplatné (duplicitní karta, neznámá karta).
// Karty jsou reprezentované jako celá čísla typu int. Číslo je tvořeno hodnotou karty a její barvou. Hodnota karty je znak '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K' nebo 'A'.
// Barva karty je určena konstantou SUITE_SPADES, SUITE_HEARTS, SUITE_CLUBS nebo SUITE_DIAMONDS. Hodnota a barva karty jsou spojené pomocí bitového operátoru or.
// Tedy například kárové eso je uložené jako SUITE_DIAMONDS | 'A'. Pro zkrácení zápisu jsou vytvořená 4 makra, tedy např. zápis kárového esa lze zkrátit na DIAMONDS('A').

// Při porovnání program vychází z pravidel pokru na Wikipedii. Vycházíme z toho, že ve hře je 52 karet, tedy karty se neopakují. To zjednodušuje porovnávání.
// Rozlišují se následující kombinace v pořadí od nejsilnější k nejslabší:
//
// čistá postupka (straight flush): 5 po sobě jdoucích karet stejné barvy. Eso může být v postupce pouze s králem (neuvažuje se postupka A 2 3 4 5). Pokud mají oba hráči čistou postupku, rozhoduje nejvyšší karta.

// 4 karty stejné hodnoty (4-of-kind) - např. 4xA + jedna další karta. Pokud oba hráči mají 4 karty stejné hodnoty, rozhoduje hodnota karty (4xA > 4xK ).

// full house: 3 karty stejné hodnoty a 2 karty stejné hodnoty (např. 3xA + 2xK). Pokud oba hráči mají full house, rozhoduje hodnota karty, kterou mají hráči 3x (3xA + 2x2 > 3xK + 2xQ).

// stejná barva (flush): všech 5 karet má stejnou barvu, např. 5x kára. Pokud oba hráči mají flush, rozhoduje se podle hodnoty nejvyšší karty. Pokud to stále nestačí k rozhodnutí, rozhoduje se podle hodnoty druhé nejvyšší karty (případně třetí nejvyšší, ...)

// postupka (straight): 5 po sobě jdoucích karet, které nemají stejnou barvu. Pokud oba hráči mají postupku, rozhoduje se podle hodnoty nejvyšší karty. Opět neuvažujeme postupku A 2 3 4 5.

// 3 karty stejné hodnoty (3-of-kind) - např. 3xA + dvě další libovolné karty. Pokud oba hráči mají 3 karty stejné hodnoty, rozhoduje hodnota karty (3xA + 1x2 + 1x3 > 3xQ + 1xJ + 1xX ).

// dva páry (two pair) - např. 2xA + 2xK + libovolná karta. Pokud oba hráči mají dva páry, rozhoduje se podle hodnoty karty ve vyšším páru. Pokud jsou stále shodné, rozhoduje hodnota karty v nižším páru. Případně pak rozhoduje hodnota zbývající karty.

// jeden pár (one pair) - např. 2xA + 3x libovolná karta. Pokud oba hráči mají jeden pár, rozhoduje se podle hodnoty karty v páru. Pokud jsou stále shodné, rozhodují hodnoty zbývajících karet v pořadí dle klesající hodnoty.

// nic (nothing) - ostatní kombinace karet, které se nedají seskupit do silnější kombinace. Pokud oba hráči nemají nic, rozhoduje se podle hodnoty karet v pořadí od nejvyšší hodnoty.


#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
constexpr int SUITE_SPADES   = 0x000;
constexpr int SUITE_HEARTS   = 0x080;
constexpr int SUITE_CLUBS    = 0x100;
constexpr int SUITE_DIAMONDS = 0x180;
constexpr int RES_DRAW       = 0;
constexpr int RES_WIN_A      = 1;
constexpr int RES_WIN_B      = -1;
constexpr int RES_INVALID    = 2;

#define SPADES(X)        ((X) | SUITE_SPADES)
#define HEARTS(X)        ((X) | SUITE_HEARTS)
#define CLUBS(X)         ((X) | SUITE_CLUBS)
#define DIAMONDS(X)      ((X) | SUITE_DIAMONDS)

#endif /* __PROGTEST__ */

typedef struct
{
  char value;
  char suite;
} HAND;

int cardValueToInt(char value)
{
  switch (value)
  {
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'X': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
    case 'A': return 14;

    default: return -1; // neznama karta
  }
}

void calculateFrequency(HAND hand[5], int freq[15])
{
  for(int i = 0; i < 15; i++)
  {
    freq[i] = 0;
  }

  for(int i = 0; i < 5; i++)
  {
    int value = cardValueToInt(hand[i].value);
    if(value >= 2 && value <= 14)
    {
      freq[value]++;
    }
  }
}


bool isFlush(HAND hand[5])
{
  for(int i = 0; i < 5; i++)
  {
    if(hand[i].suite != hand[0].suite)
    return false;
  }
  return true;
}

bool isStraight(HAND hand[5])
{
  int values[5];

  for(int i = 0; i < 5; i++)
  {
    values[i] = cardValueToInt(hand[i].value);
  }

  for(int i = 0; i < 4; i++)
  {
    for(int j = i+1; j < 5; j++)
    {
      if(values[i] > values [j])
      {
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }

  for(int i = 0; i < 4; i++)
  {
    if(values[i] + 1 != values[i + 1])
    {
      return false;
    }
  }

  return true;
}

bool isStraightFlush(HAND hand[])
{
  return (isFlush(hand) && isStraight(hand));
}

bool isFourOfAKind(HAND hand[])
{
  int freq[15];
  calculateFrequency(hand, freq);

  for(int i = 2; i <= 14; i++)
  {
    if(freq[i] == 4)
    {
        return true;
    }
  }

  return false;
}

bool isFullHouse(HAND hand[])
{
  int freq[15];
  calculateFrequency(hand, freq);

  bool foundThree = false;
  bool foundPair = false;

  for(int i = 2; i <= 14; i++)
  {
    if(freq[i] == 3)
    {
        foundThree = true;
    }
    else if(freq[i] == 2)
    {
        foundPair = true;
    }
  }

  return (foundThree && foundPair);
}

bool isThreeOfKind(HAND hand[])
{
  int freq[15];
  calculateFrequency(hand, freq);

  bool foundThree = false;

  for(int i = 2; i <= 14; i++)
  {
    if(freq[i] == 3)
    {
        foundThree = true;
        break;
    }
  }

  if(foundThree)
  {
    int singleCount = 0;

    for(int i = 2; i <= 14; i++)
    {
        if(freq[i] == 1)
        {
            singleCount++;
        }
    }

    return(singleCount == 2);
  }

  return false;
}

bool isTwoPair(HAND hand[])
{
  int freq[15];
  calculateFrequency(hand, freq);

  int pairCount = 0;
  int singleCount = 0;

  for(int i = 2; i <= 14; i++)
  {
    if(freq[i] == 2)
    {
        pairCount++;
    }
    else if(freq[i] == 1)
    {
        singleCount++;
    }
  }

  return (pairCount == 2 && singleCount == 1);
}

bool isOnePair(HAND hand[])
{
  int freq[15];
  calculateFrequency(hand, freq);

  int pairCount = 0;
  int singleCount = 0;

  for(int i = 2; i <= 14; i++)
  {
    if(freq[i] == 2)
    {
        pairCount++;
    }
    else if(freq[i] == 1)
    {
        singleCount++;
    }
  }

  return (pairCount == 1 && singleCount == 3);
}

int highCard(HAND hand[])
{
  int values[5];

  for(int i = 0; i < 5; i++)
  {
    values[i] = cardValueToInt(hand[i].value);
  }

  int maxcard = values[0];
  for(int i = 1; i < 5; i++)
  {
    if(values[i] > maxcard)
    {
      maxcard = values[i];
    }
  }

  return maxcard;
}

int getHandRank(HAND hand[])
{
  if (isStraightFlush(hand)) return 8;
  if (isFourOfAKind(hand)) return 7;
  if (isFullHouse(hand)) return 6;
  if (isFlush(hand)) return 5;
  if (isStraight(hand)) return 4;
  if (isThreeOfKind(hand)) return 3;
  if (isTwoPair(hand)) return 2;
  if (isOnePair(hand)) return 1;
  return 0;
}

void sortHand(HAND hand[])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = i + 1; j < 5; j++)
        {
            if(cardValueToInt(hand[i].value) < cardValueToInt(hand[j].value)) //od najvyssej po najnizsiu
            {
                HAND temp = hand[i];
                hand[i] = hand[j];
                hand[j] = temp;
            }
        }
    }
}

bool duplicateCards(HAND handA[], HAND handB[])
{
  HAND connectedHands[10];

  for(int i = 0; i < 5; i++)
  {
    connectedHands[i] = handA[i];
    connectedHands[i + 5] = handB[i];
  }

  for(int i = 0; i < 10; i++)
  {
    for(int j = i+1; j < 9; j++)
    {
      if(connectedHands[i].value == connectedHands[j].value && connectedHands[i].suite == connectedHands[j].suite)
      {
        return true;
      }
    }
  }

  return false;
}


int comparePokerHands ( const int playerA[], const int playerB[] )
{
  /* TODO: Your code here */

  HAND handA[5];
  HAND handB[5];

  for(int i = 0; i < 5; i++)
  {
    handA[i].value = playerA[i] & 0b01111111;
    handA[i].suite = (playerA[i] >> 7) & 0b11;
    handB[i].value = playerB[i] & 0b01111111;
    handB[i].suite = (playerB[i] >> 7) & 0b11;
  }

  for(int i = 0; i < 5; i++)
  {
    int valueA = cardValueToInt(handA[i].value);
    int valueB = cardValueToInt(handB[i].value);

    if(valueA == -1 || valueB == -1)
    {
        return RES_INVALID;
    }
  }

  if(duplicateCards(handA, handB))
  {
    return RES_INVALID;
  }

  int rankA = getHandRank(handA);
  int rankB = getHandRank(handB);

  if(rankA > rankB)
  {
    return RES_WIN_A;
  }
  else if(rankA < rankB)
  {
    return RES_WIN_B;
  }
  else
  {
    sortHand(handA);
    sortHand(handB);

    if(isStraight(handA) && isStraight(handB))
    {
      for(int i = 0; i < 5; i++)
      {
        int valueA = cardValueToInt(handA[i].value);
        int valueB = cardValueToInt(handB[i].value);

        if(valueA > valueB)
        {
            return RES_WIN_A;
        }
        else if(valueA < valueB)
        {
            return RES_WIN_B;
        }
      } 
    }

    if(isFlush(handA) && isFlush(handB))
    {
      for(int i = 0; i < 5; i++)
      {
        int valueA = cardValueToInt(handA[i].value);
        int valueB = cardValueToInt(handB[i].value);

        if(valueA > valueB)
        {
            return RES_WIN_A;
        }
        else if(valueA < valueB)
        {
            return RES_WIN_B;
        }
      } 
    }

    if(isStraightFlush(handA) && isStraightFlush(handB))
    {
      int valueA = highCard(handA);
      int valueB = highCard(handB);

      if(valueA > valueB)
      {
        return RES_WIN_A;
      }
      else if(valueA < valueB)
      {
        return RES_WIN_B;
      }
    }

    if(isFourOfAKind(handA) && isFourOfAKind(handB))
    {
      int freqA[15], freqB[15];
      calculateFrequency(handA, freqA);
      calculateFrequency(handB, freqB);

      int fourA = -1, fourB = -1, singleA = -1, singleB = -1;

      for(int i = 2; i <= 14; i++)
      {
        if(freqA[i] == 4)
        {
          fourA = i;
        }
        else if(freqA[i] == 1)
        {
          singleA = i;
        }

        if(freqB[i] == 4)
        {
          fourB = i;
        }
        else if(freqB[i] == 1)
        {
          singleB = i;
        }
      }

      if(fourA > fourB) return RES_WIN_A;
      if(fourA < fourB) return RES_WIN_B;
      if(singleA > singleB) return RES_WIN_A;
      if(singleA < singleB) return RES_WIN_B;
    }

    if(isFullHouse(handA) && isFullHouse(handB))
    {
      int freqA[15], freqB[15];
      calculateFrequency(handA, freqA);
      calculateFrequency(handB, freqB);

      int threeA = -1, threeB = -1, pairA = -1, pairB = -1;

      for(int i = 2; i <= 14; i++)
      {
        if(freqA[i] == 3)
        {
          threeA = i;
        }
        else if(freqA[i] == 2)
        {
          pairA = i;
        }

        if(freqB[i] == 3)
        {
          threeB = i;
        }
        else if(freqB[i] == 2)
        {
          pairB = i;
        }
      }

      if(threeA > threeB) return RES_WIN_A;
      if(threeA < threeB) return RES_WIN_B;
      if(pairA > pairB) return RES_WIN_A;
      if(pairA < pairB) return RES_WIN_B;
    }

    if(isThreeOfKind(handA) && isThreeOfKind(handB))
    {
      int freqA[15], freqB[15];
      calculateFrequency(handA, freqA);
      calculateFrequency(handB, freqB);

      int threeA = -1, threeB = -1, singleA1 = -1, singleA2 = -1, singleB1 = -1, singleB2 = -1;

      for(int i = 2; i <= 14; i++)
      {
        if(freqA[i] == 3)
        {
          threeA = i;
        }
        else if(freqA[i] == 1)
        {
          if(singleA1 == -1)
          {
            singleA1 = i;
          }
          else
          {
            singleA2 = i;
          }
        }

        if(freqB[i] == 3)
        {
          threeB = i;
        }
        else if(freqB[i] == 1)
        {
          if(singleB1 == -1)
          {
            singleB1 = i;
          }
          else
          {
            singleB2 = i;
          }
        }
      }

      if(threeA > threeB) return RES_WIN_A;
      if(threeA < threeB) return RES_WIN_B;
      if(singleA1 > singleB1) return RES_WIN_A;
      if(singleA1 < singleB1) return RES_WIN_B;
      if(singleA2 > singleB2) return RES_WIN_A;
      if(singleA2 < singleB2) return RES_WIN_B;
    }

    if(isTwoPair(handA) && isTwoPair(handB))
    {
      int freqA[15], freqB[15];
      calculateFrequency(handA, freqA);
      calculateFrequency(handB, freqB);

      int pairA1 = -1, pairA2 = -1, pairB1 = -1, pairB2 = -1, singleA = -1, singleB = -1;

      for(int i = 2; i <= 14; i++)
      {
        if(freqA[i] == 2)
        {
          if(pairA1 == -1)
          {
            pairA1 = i;
          }
          else
          {
            pairA2 = i;
          }
        }
        else if(freqA[i] == 1)
        {
          singleA = i;
        }

        if(freqB[i] == 2)
        {
          if(pairB1 == -1)
          {
            pairB1 = i;
          }
          else
          {
            pairB2 = i;
          }
        }
        else if(freqB[i] == 1)
        {
          singleB = i;
        }
      }

      if(pairA1 > pairB1) return RES_WIN_A;
      if(pairA1 < pairB1) return RES_WIN_B;
      if(pairA2 > pairB2) return RES_WIN_A;
      if(pairA2 < pairB2) return RES_WIN_B;
      if(singleA > singleB) return RES_WIN_A;
      if(singleA < singleB) return RES_WIN_B;
    }

    if(isOnePair(handA) && isOnePair(handB))
    {
      int freqA[15], freqB[15];
      calculateFrequency(handA, freqA);
      calculateFrequency(handB, freqB);

      int pairA = -1, pairB = -1, singleA1 = -1, singleA2 = -1, singleB1 = -1, singleB2 = -1;

      for(int i = 2; i <= 14; i++)
      {
        if(freqA[i] == 2)
        {
          pairA = i;
        }
        else if(freqA[i] == 1)
        {
          if(singleA1 == -1)
          {
            singleA1 = i;
          }
          else
          {
            singleA2 = i;
          }
        }

        if(freqB[i] == 2)
        {
          pairB = i;
        }
        else if(freqB[i] == 1)
        {
          if(singleB1 == -1)
          {
            singleB1 = i;
          }
          else
          {
            singleB2 = i;
          }
        }
      }

      if(pairA > pairB) return RES_WIN_A;
      if(pairA < pairB) return RES_WIN_B;
      if(singleA1 > singleB1) return RES_WIN_A;
      if(singleA1 < singleB1) return RES_WIN_B;
      if(singleA2 > singleB2) return RES_WIN_A;
      if(singleA2 < singleB2) return RES_WIN_B;
    }
  }

  for(int i = 0; i < 5; i++)
    {
        int valueA = cardValueToInt(handA[i].value);
        int valueB = cardValueToInt(handB[i].value);

        if(valueA > valueB)
        {
            return RES_WIN_A;
        }
        else if(valueA < valueB)
        {
            return RES_WIN_B;
        }
    }

  return RES_DRAW;
}

#ifndef __PROGTEST__
int main ()
{
  int x0[] = { SPADES('5'), HEARTS('5'), CLUBS('5'), DIAMONDS('5'), HEARTS('X') };
  int y0[] = { SPADES('6'), SPADES('9'), SPADES('8'), SPADES('X'), SPADES('7') };
  assert ( comparePokerHands ( x0, y0 ) == RES_WIN_B );

  int x1[] = { SPADES('2'), HEARTS('2'), CLUBS('2'), SPADES('A'), DIAMONDS('2') };
  int y1[] = { CLUBS('A'), HEARTS('K'), HEARTS('A'), SPADES('K'), DIAMONDS('A') };
  assert ( comparePokerHands ( x1, y1 ) == RES_WIN_A );

  int x2[] = { CLUBS('3'), HEARTS('2'), HEARTS('3'), SPADES('2'), DIAMONDS('3') };
  int y2[] = { CLUBS('A'), CLUBS('9'), CLUBS('Q'), CLUBS('4'), CLUBS('J') };
  assert ( comparePokerHands ( x2, y2 ) == RES_WIN_A );

  int x3[] = { DIAMONDS('3'), HEARTS('7'), SPADES('5'), DIAMONDS('6'), SPADES('4') };
  int y3[] = { CLUBS('2'), CLUBS('4'), CLUBS('6'), CLUBS('3'), CLUBS('X') };
  assert ( comparePokerHands ( x3, y3 ) == RES_WIN_B );

  int x4[] = { DIAMONDS('3'), HEARTS('7'), SPADES('5'), DIAMONDS('6'), SPADES('4') };
  int y4[] = { CLUBS('2'), DIAMONDS('2'), CLUBS('6'), CLUBS('3'), HEARTS('2') };
  assert ( comparePokerHands ( x4, y4 ) == RES_WIN_A );

  int x5[] = { DIAMONDS('3'), HEARTS('7'), SPADES('3'), DIAMONDS('6'), SPADES('7') };
  int y5[] = { CLUBS('2'), DIAMONDS('2'), CLUBS('6'), CLUBS('3'), HEARTS('2') };
  assert ( comparePokerHands ( x5, y5 ) == RES_WIN_B );

  int x6[] = { DIAMONDS('3'), HEARTS('7'), SPADES('3'), DIAMONDS('6'), SPADES('7') };
  int y6[] = { CLUBS('2'), DIAMONDS('9'), CLUBS('K'), CLUBS('A'), HEARTS('2') };
  assert ( comparePokerHands ( x6, y6 ) == RES_WIN_A );

  int x7[] = { DIAMONDS('A'), HEARTS('J'), SPADES('Q'), DIAMONDS('X'), SPADES('2') };
  int y7[] = { CLUBS('2'), DIAMONDS('9'), CLUBS('K'), CLUBS('A'), HEARTS('2') };
  assert ( comparePokerHands ( x7, y7 ) == RES_WIN_B );

  int x8[] = { DIAMONDS('A'), HEARTS('J'), SPADES('Q'), DIAMONDS('X'), SPADES('2') };
  int y8[] = { CLUBS('Q'), DIAMONDS('K'), CLUBS('2'), CLUBS('A'), HEARTS('3') };
  assert ( comparePokerHands ( x8, y8 ) == RES_WIN_B );

  int x9[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y9[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x9, y9 ) == RES_WIN_A );

  int x10[] = { CLUBS('A'), CLUBS('2'), CLUBS('3'), CLUBS('4'), CLUBS('5') };
  int y10[] = { HEARTS('J'), CLUBS('J'), SPADES('J'), HEARTS('2'), SPADES('2') };
  assert ( comparePokerHands ( x10, y10 ) == RES_WIN_B );

  int x11[] = { CLUBS('A'), CLUBS('K'), CLUBS('Q'), CLUBS('J'), CLUBS('X') };
  int y11[] = { HEARTS('3'), CLUBS('3'), SPADES('3'), HEARTS('2'), SPADES('2') };
  assert ( comparePokerHands ( x11, y11 ) == RES_WIN_A );

  int x12[] = { CLUBS('A'), HEARTS('A'), CLUBS('Q'), HEARTS('Q'), CLUBS('J') };
  int y12[] = { SPADES('A'), DIAMONDS('A'), SPADES('Q'), DIAMONDS('Q'), SPADES('J') };
  assert ( comparePokerHands ( x12, y12 ) == RES_DRAW );

  int x13[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y13[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), HEARTS('5'), HEARTS('4') };
  assert ( comparePokerHands ( x13, y13 ) == RES_INVALID );

  int x14[] = { DIAMONDS('A'), HEARTS('Z'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y14[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x14, y14 ) == RES_INVALID );

  int x17[] = { DIAMONDS('J'), CLUBS('J'), HEARTS('J'), SPADES('5'), SPADES('J') };
  int y17[] = { SPADES('4'), CLUBS('4'), DIAMONDS('4'), HEARTS('4'), SPADES('Q') };
  assert ( comparePokerHands ( x17, y17 ) == RES_WIN_A );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

