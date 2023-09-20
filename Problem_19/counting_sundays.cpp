
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int32_t b32;

enum Day_Type {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,

    Day_Count,
};

enum Month_Type {
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December,

    Month_Count,
};

struct Day_Buffer {
    Day_Type day;
    Day_Buffer *next;
};

struct Month_Buffer {
    Month_Type month;
    Month_Buffer *next;
};

struct Date {
    Day_Buffer *date_day;
    Month_Buffer *date_month;
    u16 date_number;
    u16 year;
};

static void InitDayBuffer(Date *date) {
    if (date) {
        Day_Buffer *head    = NULL;
        Day_Buffer *current = NULL;
        Day_Buffer *prev    = NULL;

        for (u32 index = Monday; index < Day_Count; index++) {
            current       = (Day_Buffer *)malloc(sizeof(Day_Buffer));
            current->day  = (Day_Type)index;
            current->next = NULL;

            if (prev) {
                prev->next = current;
            } else {
                head = current;
            }

            prev = current;
        }

        current->next  = head;
        date->date_day = head;
    }
}

static void InitMonthBuffer(Date *date) {
    if (date) {
        Month_Buffer *head    = NULL;
        Month_Buffer *current = NULL;
        Month_Buffer *prev    = NULL;

        for (u32 index = January; index < Month_Count; index++) {
            current        = (Month_Buffer *)malloc(sizeof(Month_Buffer));
            current->month = (Month_Type)index;
            current->next  = NULL;

            if (prev) {
                prev->next = current;
            } else {
                head = current;
            }

            prev = current;
        }

        current->next    = head;
        date->date_month = head;
    }
}

static void IncrementDays(Date *date, u32 days_in_month) {
    for (int index = 1; index < 30; index++) {
        date->date_number++;  
        date->date_day = date->date_day->next;
    }
}

static void StartCalendar() {
}

int main() {
    Date date;

    InitDayBuffer(&date);
    InitMonthBuffer(&date);
    date.year = 1901;
    date.date_day = date.date_day->next;
    date.date_number = 1;
    u32 sunday_count = 0;
    
    while (date.year != 2001) {
        switch (date.date_month->month) {
            case September:
            case April:
            case June:
            case November: {
                u32 month_days = 30;
                IncrementDays(&date, month_days);
            } break;

            case January:
            case March:
            case May:
            case July:
            case August:
            case October:
            case December: {
                u32 month_days = 31;
                IncrementDays(&date, month_days);
                if (date.date_month->month == December) {
                    date.year++;
                }
            } break;

            case February: {
                u8 feb_days = date.year % 4 == 0 ? 29 : 28;
                if (date.year % 100 == 0) {
                    feb_days = date.year % 400 == 0 ? 29 : 28;
                }
                IncrementDays(&date, feb_days);
            } break;
        }

        date.date_month  = date.date_month->next;
        date.date_number = 1;
        date.date_day = date.date_day->next;
        if (date.date_day->day == Sunday) {
            sunday_count++;
        }
    }

    printf("%d/%d/%d is a %d with %d Sundays\n", date.date_number, date.date_month->month, date.year, date.date_day->day, sunday_count);
}
