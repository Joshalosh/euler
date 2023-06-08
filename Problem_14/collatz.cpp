#include <iostream>
#include <stdint.h>

#define Array_Count(array) (sizeof(array) / sizeof((array)[0]))

#define Assert(expression) if(!(expression)) {*(int *)0 = 0;}

int main()
{
    int largest_count = 0;
    int largest_num = 0;
    int64_t largest_sequence[4096] = {};

    for(int index = 3; index < 100000; index += 2)
    {
        int64_t temp_sequence[4096] = {};
        int64_t num = index;
        int count = 1;
        int original_count;
        bool is_done;
        while(num != 1)
        {
            Assert(num > 0);

            is_done = false;
            for(int i = 0; i < largest_count; i++) 
            {
                if(num == largest_sequence[i])
                {
                    original_count = count;
                    count += largest_count - 1 - i;
                    is_done = true;
                    break;
                }
            }

            if(!is_done)
            {
                if(num % 2 == 0)
                {
                    num /= 2;
                }
                else
                {
                    num *= 3;
                    num += 1;
                }

                temp_sequence[count] = num;
                count++;
            }
            else 
            {
                num = 1;
            }
        }

        if(count > largest_count)
        {
            int sequence_count = is_done ? original_count : count;

            temp_sequence[0] = index;
            int64_t new_array[4096] = {};
            for(int i = 0; i < sequence_count; i++)
            {
                new_array[i] = temp_sequence[i];
            }

            for(int i = sequence_count; i < largest_count; i++)
            {
                new_array[i] = largest_sequence[i];
            }

            largest_count = count;

            for(int i = 0; i < largest_count; i++)
            {
                largest_sequence[i] = new_array[i];
            }

            largest_num = index;
        }
    }

    printf("\nLargest number: %d   Largest Count: %d", largest_num, largest_count);
}
