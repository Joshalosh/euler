
#include <stdlib.h>
#include <stdio.h>

char *ones_buffer[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *teens_buffer[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *tens_buffer[] = {"error", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
char buffer[100000];
int buffer_count = 0;

static void StringifyNumber() {
    for (int num = 1; num <= 1000; num++) {
        if (num < 10) {
            buffer_count += sprintf(buffer+buffer_count, "%s", ones_buffer[num - 1]);
        } else if (num >= 10 && num < 100) {
            if (num >= 10 && num < 20) {
                int teens = num % 10;
                buffer_count += sprintf(buffer+buffer_count, "%s", teens_buffer[teens]);
            } else {
                int tens = num / 10;
                int ones = num % 10;
                buffer_count += sprintf(buffer+buffer_count, "%s", tens_buffer[tens - 1]);
                if (ones) {
                    buffer_count += sprintf(buffer+buffer_count, "%s", ones_buffer[ones - 1]);
                }
            }
        } else if (num >= 100 && num < 1000) {
            int hundreds = num / 100;
            int tens = num % 100;
            int ones = tens % 10;
            if (!tens) {
                buffer_count += sprintf(buffer+buffer_count, "%shundred", ones_buffer[hundreds-1]);
            } else {
                buffer_count += sprintf(buffer+buffer_count, "%shundredand", ones_buffer[hundreds-1]);

                if (tens >= 10 && tens < 20) {
                    tens = tens % 10;
                    buffer_count += sprintf(buffer+buffer_count, "%s", teens_buffer[tens]);
                } else if (tens >= 20) {
                    buffer_count += sprintf(buffer+buffer_count, "%s", tens_buffer[(tens/10)-1]);
                    if (ones) {
                        buffer_count += sprintf(buffer+buffer_count, "%s", ones_buffer[ones - 1]);
                    }
                } else {
                    buffer_count += sprintf(buffer+buffer_count, "%s", ones_buffer[ones - 1]); 
                }
            }
        } else {
            buffer_count += sprintf(buffer+buffer_count, "onethousand");
        }
    }
    printf("%d\n", buffer_count);
}

int main() {
    StringifyNumber();
}
