
#include <stdio.h>

static int SumOfProperDivisors(int num) {
    int sum = 0;
    for (int divisor = 1; divisor <= num / 2; divisor++) {
        if (num % divisor == 0) {
            sum += divisor;
        }
    }

    return sum;
}

int main() {
    int amicable_number_count = 0;
    int amicable_sum = 0;
    for (int first_num = 2; first_num < 10000; first_num++) {
        int second_num = SumOfProperDivisors(first_num);

        if(second_num != first_num)
        {
            if (SumOfProperDivisors(second_num) == first_num) {
                printf("%d and %d are amicable numbers\n", first_num, second_num);
                amicable_number_count++;
                amicable_sum += first_num;
            }
        }
    }

    printf("The number of amicable numbers under 1000 are: %d\n", amicable_number_count);
    printf("%d\n", amicable_sum);

}
