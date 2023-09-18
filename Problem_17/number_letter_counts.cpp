
#include <stdio.h>

char *ones_buffer[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *teens_buffer[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *tens_buffer[] = {"error", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static void StringifyNumber() {
    for (int num = 1; num <= 100; num++) {
        if (num < 10) {
            printf("%s ", ones_buffer[num - 1]);
        } else if (num >= 10 && num < 100) {
            if (num >= 10 && num < 20) {
                int teens = num % 10;
                printf("%s ", teens_buffer[teens - 1]);
            } else {
                int tens = num / 10;
                int ones = num % 10;
                printf("%s ", tens_buffer[tens - 1]);
                if (ones) {
                    printf("%s ", ones_buffer[ones - 1]);
                }
            }
        } else if (num >= 100 && num < 1000) {
            int hundreds = num / 100;
            int tens = num % 100;
            int ones = tens % 10;
            printf("%s hundred and ", ones_buffer[hundreds-1]);
            if (tens >= 10 && tens < 20) {
                tens = tens % 10;
                printf("%s ", teens_buffer[tens - 1]);
            } else if (tens >= 20) {
                printf("%s ", tens_buffer[(tens/10)-1]);
                if (ones) {
                    printf("%s ", ones_buffer[ones - 1]);
                }
            } else {
                printf("%s ", ones_buffer[ones - 1]); 
            }
        }
    }

    printf("\n");
}

int main() {
    StringifyNumber();
}
