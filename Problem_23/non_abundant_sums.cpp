#include <stdio.h>

#define ARRAY_COUNT(array) sizeof(array) / sizeof((array)[0])
#define MAX_NUM 28123

int main()
{
    int abundants_array[MAX_NUM] = {};
    int abundants_index = 0;
    for (int i = 2; i < MAX_NUM; i++) {
        int divisors = 0;
        for (int j = 1; j <= i / 2; j++) {
            if (i % j == 0) {
                divisors += j;
            }
        }

        if (divisors > i) {
            abundants_array[abundants_index] = i;
            abundants_index++;
        }
    }

    // NOTE: Using a sparse array to hold all the potential abundant sums 
    // for fast loop ups
    int abundant_sums_array[MAX_NUM] = {};
    for (int outer = 0; outer < abundants_index; outer++) {
        for(int inner = outer; inner < abundants_index; inner++) {
            int sum = abundants_array[outer] + abundants_array[inner];
            if (sum < MAX_NUM && !abundant_sums_array[sum]) {
                abundant_sums_array[sum] = sum;
            }
        }
    }

    int non_abundant_sum = 0;
    for(int i = 1; i < MAX_NUM; i++) {
        // NOTE: Check all the positive integers against the sparse array. 
        // If there is no entry this is a valid number to sum
        if (!abundant_sums_array[i]) {
            non_abundant_sum += i;
        }
    }

    printf("The sum of all non abundant numbers is: %d\n", non_abundant_sum);
}
