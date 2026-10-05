// Úkolem je realizovat funkce (ne celý program, pouze funkce), které budou usnadňovat plánování dopravy.
//
// Předpokládáme dopravní spojení dvou míst A a B. V jeden den jede z A do B nula nebo více spojů. Počet spojů je daný celým číslem.
// Dále můžeme omezit konkrétní dny v týdnu, ve kterých spoj jezdí. Například můžeme definovat, že spojení je v provozu v pondělí, v pátek a v sobotu (v ostatní dny týdne ne).
// Pro zjednodušení uvažujeme, že počet spojů je daný jedním celým číslem perWorkDay:
//
// pokud je spojení v provozu v daný všední den, pak jede perWorkDay spojů,
// pokud je spojení v provozu v sobotu, pak jede perWorkDay / 2 spojů, desetinnou část zaokrouhlíme nahoru,
// pokud je spojení v provozu v neděli, pak jezdí perWorkDay / 3 spojů, desetinnou část zaokrouhlíme nahoru.
// Následující tabulka shrnuje počty spojení za jeden týden pro různé kombinace perWorkDay a masku dní v týdnu dowMask:
//
//  							perWorkDay = 6	perWorkDay = 19
// DOW_MON						6				19
// DOW_SAT						3				10
// DOW_SUN						2				7
// DOW_WORKDAYS					5 × 6			5 × 19
// DOW_WEEKEND					3 + 2			10 + 7
// DOW_ALL						5 × 6 + 3 + 2	5 × 19 + 10 + 7
// DOW_MON | DOW_THU | DOW_SUN	2 × 6 + 2		2 × 19 + 7

// Pro plánování potřebujeme vědět, kolik spojů bude celkem potřeba objednat v zadaném časovém intervalu. Dále se hodí i opačná funkce na výpočet časového intervalu, který lze pokrýt objednaným počtem spojů. Tyto výpočty budou realizované požadovanými funkcemi:
//
// countConnections ( from, to, perWorkDay, dowMask )
// funkce dostane v parametrech časový interval <from; to>, počet spojů během jednoho všedního dne perWorkDay a masku dní v týdnu, kdy je spoj v provozu dowMask.
// Na základě těchto parametrů funkce vypočte počet spojů, které je potřeba objednat pro pokrytí zadaného intervalu dní. Interval chápeme jako uzavřený, tedy obsahuje celý první i celý poslední den.
// Pokud jsou parametry neplatné, funkce vrátí hodnotu -1. Za chybu považujeme:
// neplatné datum from nebo to nebo
// počátek intervalu from nastane po konci intervalu to (tj. nesprávné je from > to).
// Implementace této funkce je Vaším úkolem.

// endDate ( from, connections, perWorkDay, dowMask )
// funkce dostane počáteční datum from, počet objednaných spojení connections, počet spojů během jednoho všedního dne perWorkDay a masku dní v týdnu, kdy je spoj v provozu dowMask.
// Na základě těchto parametrů funkce vypočte datum posledního dne, který jsme se zadaným počtem spojeni schopni pokrýt (tj. pro další den již nebude dostatek objednaných spojení).
// Návratovou hodnotou je nalezené datum nebo datum 0000-00-00 pro neplatnou kombinaci parametrů:
// neplatné datum from,
// záporný počet objednaných spojení connections,
// počet objednaných spojení connections nestačí ani na den from,
// nulová hodnota spojení perWorkDay nebo
// prázdná maska dowMask.
// Implementace této funkce je Vaším úkolem.

// TDATE
// je struktura reprezentující datum. Tvoří ji složky rok, měsíc a den. Struktura je deklarovaná v testovacím prostředí, Vaše implementace ji může/musí používat.
// Nelze ale měnit deklaraci struktury.

// makeDate(y, m, d)
// pomocná funkce deklarovaná v testovacím prostředí. Funkci můžete použít pro usnadnění ladění. Implementaci nelze změnit.

// konstanty DOW_MON, DOW_TUE, ..., DOW_ALL
// konstanty jsou deklarované v testovacím prostředí a nelze je měnit. Používají se pro masky dní, ve kterých spoj jezdí.

// Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Rozumná implementace naivního algoritmu by měla projít všemi testy kromě testů rychlosti. Pro zvládnutí testů rychlosti je potřeba použít výkonnější algoritmus.

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

constexpr unsigned DOW_MON      = 0b0000'0001;
constexpr unsigned DOW_TUE      = 0b0000'0010;
constexpr unsigned DOW_WED      = 0b0000'0100;
constexpr unsigned DOW_THU      = 0b0000'1000;
constexpr unsigned DOW_FRI      = 0b0001'0000;
constexpr unsigned DOW_SAT      = 0b0010'0000;
constexpr unsigned DOW_SUN      = 0b0100'0000;
constexpr unsigned DOW_WORKDAYS = DOW_MON | DOW_TUE | DOW_WED | DOW_THU | DOW_FRI;
constexpr unsigned DOW_WEEKEND  = DOW_SAT | DOW_SUN;
constexpr unsigned DOW_ALL      = DOW_WORKDAYS | DOW_WEEKEND;

typedef struct TDate
{
  unsigned m_Year;
  unsigned m_Month;
  unsigned m_Day;
} TDATE;

TDATE makeDate ( unsigned y,
                 unsigned m,
                 unsigned d )
{
  TDATE res = { y, m, d };
  return res;
}
#endif /* __PROGTEST__ */

int dow[] = {DOW_MON, DOW_TUE, DOW_WED, DOW_THU, DOW_FRI, DOW_SAT, DOW_SUN};

int is_leap_year(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0 && year % 4000 != 0);
}

unsigned days_in_month(int year, int month)
{
  int months_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if(month == 2 && is_leap_year(year))
  {
    return 29;
  }
  
  return months_days[month - 1];
}

int days_from_start(int day, int month, int year)
{
  int days = day;

  for(int y = 1; y < year; y++)
  {
    days += (is_leap_year(y)) ? 366 : 365;
  }

  for(int m = 1; m < month; m++)
  {
    days += days_in_month(year, m);
  }

  return days;
}

int date_difference(TDATE date1, TDATE date2)
{
  int days1 = days_from_start(date1.m_Day, date1.m_Month, date1.m_Year);
  int days2 = days_from_start(date2.m_Day, date2.m_Month, date2.m_Year);

  return fabs(days1 - days2) + 1;
}

int day_of_week(TDATE date)
{
  if(date.m_Month < 3)
  {
    date.m_Month += 12;
    date.m_Year -= 1;
  }

  long long k = date.m_Year % 100;
  long long j = date.m_Year / 100;

  int dayOfWeek = (date.m_Day + 13 * (date.m_Month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

  return (dayOfWeek + 5) % 7;

}

TDATE next_day(TDATE date)
{
    date.m_Day++;

    if(date.m_Day > days_in_month(date.m_Year, date.m_Month))
    {
        date.m_Day = 1;
        date.m_Month++;

        if(date.m_Month > 12)
        {
            date.m_Month = 1;
            date.m_Year++;
        }
    }

    return date;
}

TDATE day_before(TDATE date)
{
    date.m_Day--;

    if(date.m_Day < 1)
    {
        date.m_Day = days_in_month(date.m_Year, date.m_Month--);
        date.m_Month--;

        if(date.m_Month == 1)
        {
            date.m_Month = 12;
            date.m_Year--;
        }
    }

    return date;
}


long long countConnections ( TDATE     from,
                             TDATE     to,
                             unsigned  perWorkDay,
                             unsigned  dowMask )
{

  if(from.m_Year > to.m_Year || (from.m_Year == to.m_Year && from.m_Month > to.m_Month) || (from.m_Month == to.m_Month && from.m_Day > to.m_Day)
    || (!is_leap_year(from.m_Year) && from.m_Month == 2 && from.m_Day == 29)
    || (!is_leap_year(to.m_Year) && to.m_Month == 2 && to.m_Day == 29)
    || ((from.m_Day || from.m_Month || from.m_Year) < 1)
    || ((to.m_Day || to.m_Month || to.m_Year) < 1)
    || (from.m_Day > days_in_month(from.m_Year, from.m_Month))
    || (to.m_Day > days_in_month(to.m_Year, to.m_Month))
    || (from.m_Month < 1 || from.m_Month > 12)
    || (to.m_Month < 1 || to.m_Month > 12)
    || (from.m_Year < 1)
    || (to.m_Year < 1))
  {
    return -1;
  }

  long long daysInInterval = date_difference(from, to);
  int startDow = day_of_week(from);
  long long fullWeeks = daysInInterval / 7;
  int remainingDays = daysInInterval % 7;

  long long totalConnections = 0;

  for(int i = 0; i < 7; i++)
  {
    if(dowMask & dow[i])
    {
      if(i < 5)
      {
        totalConnections += fullWeeks * perWorkDay;
      }
      else if(i == 5)
      {
        totalConnections += fullWeeks * ((perWorkDay + 1)/2);
      }
      else
      {
        totalConnections += fullWeeks * ((perWorkDay + 2)/3);
      }
    }
  }

  for(int i = 0; i < remainingDays; i++)
  {
    int currentDow = (startDow + i) % 7;
    if(dowMask & dow[currentDow])
    {
      if(currentDow < 5)
      {
        totalConnections += perWorkDay;
      }
      else if(currentDow == 5)
      {
        totalConnections += (perWorkDay + 1)/2;
      }
      else
      {
        totalConnections += (perWorkDay + 2)/3;
      } 
    }
  }

  return totalConnections;

}

TDATE     endDate          ( TDATE     from,
                             long long connections,
                             unsigned  perWorkDay,
                             unsigned  dowMask )
{
  // todo
    if((!is_leap_year(from.m_Year) && from.m_Month == 2 && from.m_Day == 29)
        || connections < 0 || perWorkDay == 0 || dowMask == 0
        || ((from.m_Day || from.m_Month || from.m_Year) < 1)
        || (from.m_Day > days_in_month(from.m_Year, from.m_Month))
        || (from.m_Month < 1 || from.m_Month > 12)
        || (from.m_Year < 1))
    {
        return makeDate(0,0,0);
    }

    TDATE currentDate = from;
    int currentDow = day_of_week(currentDate);
    int dow_next_day = (currentDow + 1) % 7;

    if (dowMask & dow[currentDow])
    {
        long long dailyConnections = 0;
        if (currentDow < 5)
        {
            dailyConnections = perWorkDay;
        }
        else if (currentDow == 5)
        {
            dailyConnections = ceil((double)perWorkDay / 2);
        }
        else
        {
            dailyConnections = ceil((double)perWorkDay / 3);
        }

        if (connections < dailyConnections)
        {
            return makeDate(0, 0, 0);
        }
    }


    while (connections > 0)
    {
        
        long long dailyConnections = 0;
        double half = (double)perWorkDay/2;
        double third = (double)perWorkDay/3;

        if(dowMask & dow[currentDow])
        {
            if(currentDow < 5)
            {
                dailyConnections += perWorkDay;
            }
            else if(currentDow == 5)
            {
                dailyConnections += ceil(half);
            }
            else
            {
                dailyConnections += ceil(third);
            }
        }

        if(connections == dailyConnections)
        {
            while(!(dowMask & dow[dow_next_day]))
            {
              currentDate = next_day(currentDate);
              currentDow = (currentDow + 1) % 7;
              dow_next_day = (currentDow + 1) % 7;
            }

            return currentDate;
        }
        else if(connections < dailyConnections)
        {
            return day_before(currentDate);
        }
        else
        {
            connections -= dailyConnections;
            currentDate = next_day(currentDate);
            currentDow = (currentDow + 1) % 7;
        }
    }

    return currentDate;

}


#ifndef __PROGTEST__
int main ()
{
  TDATE d;
  assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 31 ), 1, DOW_ALL ) == 31 );
  assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 31 ), 10, DOW_ALL ) == 266 );
  assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 31 ), 1, DOW_WED ) == 5 );
  assert ( countConnections ( makeDate ( 2024, 10, 2 ), makeDate ( 2024, 10, 30 ), 1, DOW_WED ) == 5 );
  assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 1 ), 10, DOW_TUE ) == 10 );
  assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 1 ), 10, DOW_WED ) == 0 );
  assert ( countConnections ( makeDate ( 2024, 1, 1 ), makeDate ( 2034, 12, 31 ), 5, DOW_MON | DOW_FRI | DOW_SAT ) == 7462 );
  assert ( countConnections ( makeDate ( 2024, 1, 1 ), makeDate ( 2034, 12, 31 ), 0, DOW_MON | DOW_FRI | DOW_SAT ) == 0 );
  assert ( countConnections ( makeDate ( 2024, 1, 1 ), makeDate ( 2034, 12, 31 ), 100, 0 ) == 0 );
  assert ( countConnections ( makeDate ( 2024, 10, 10 ), makeDate ( 2024, 10, 9 ), 1, DOW_MON ) == -1 );
  assert ( countConnections ( makeDate ( 2024, 2, 29 ), makeDate ( 2024, 2, 29 ), 1, DOW_ALL ) == 1 );
  assert ( countConnections ( makeDate ( 2023, 2, 29 ), makeDate ( 2023, 2, 29 ), 1, DOW_ALL ) == -1 );
  assert ( countConnections ( makeDate ( 2100, 2, 29 ), makeDate ( 2100, 2, 29 ), 1, DOW_ALL ) == -1 );
  assert ( countConnections ( makeDate ( 2400, 2, 29 ), makeDate ( 2400, 2, 29 ), 1, DOW_ALL ) == 1 );
  assert ( countConnections ( makeDate ( 4000, 2, 29 ), makeDate ( 4000, 2, 29 ), 1, DOW_ALL ) == -1 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, DOW_ALL );
  assert ( d . m_Year == 2025 && d . m_Month == 1 && d . m_Day == 8 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 6, DOW_ALL );
  assert ( d . m_Year == 2024 && d . m_Month == 10 && d . m_Day == 20 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, DOW_WORKDAYS );
  assert ( d . m_Year == 2025 && d . m_Month == 2 && d . m_Day == 17 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 4, DOW_WORKDAYS );
  assert ( d . m_Year == 2024 && d . m_Month == 11 && d . m_Day == 4 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, DOW_THU );
  assert ( d . m_Year == 2026 && d . m_Month == 9 && d . m_Day == 2 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 2, DOW_THU );
  assert ( d . m_Year == 2025 && d . m_Month == 9 && d . m_Day == 17 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 0, DOW_THU );
  assert ( d . m_Year == 0 && d . m_Month == 0 && d . m_Day == 0 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, 0 );
  assert ( d . m_Year == 0 && d . m_Month == 0 && d . m_Day == 0 );
  d = endDate ( makeDate ( 2024, 10, 1 ), 3, 5, DOW_ALL );
  assert ( d . m_Year == 0 && d . m_Month == 0 && d . m_Day == 0 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
