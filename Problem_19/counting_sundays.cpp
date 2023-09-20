
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

        current->next = head;
        date->date_day = head;
    }
}

static void InitMonthBuffer(Date *date) {
    if (date) {
        Month_Buffer *head    = NULL;
        Month_Buffer *current = NULL;
        Month_Buffer *prev    = NULL;

        for (u32 index = January; index < Month_Count; index++) {
            current = (Month_Buffer *)malloc(sizeof(Month_Buffer));
            current->month = (Month_Type)index;
            current->next = NULL;

            if (prev) {
                prev->next = current;
            } else {
                head = current;
            }

            prev = current;
        }

        current->next = head;
        date->date_month = head;
    }
}

static void StartCalendar() {
}

int main() {
    Date date;

    InitDayBuffer(&date);
    InitMonthBuffer(&date);
}
