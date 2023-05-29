#include <iostream>

#define Array_Count(array) (sizeof(array) / sizeof((array)[0]))

int main()
{
    int largest_count = 0;
    int largest_num = 0;
    int largest_sequence[4096] = {};

    for(int index = 3; index < 100000; index += 2)
    {
        int temp_sequence[4096] = {};
        int num = index;
        int count = 1;
        int original_count;
        bool is_done;
        while(num != 1)
        {
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

            if(is_done)
                break;

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

        if(count > largest_count)
        {
            int sequence_count = is_done ? original_count : count;

            temp_sequence[0] = index;
            for(int i = 0; i < sequence_count; i++)
            {
                largest_sequence[i] = temp_sequence[i];
            }
            largest_count = count;
            largest_num = index;
        }

        //printf("\nIndex:%d.  Count: %d", index, count);
    }

    printf("\nLargest number: %d   Largest Count: %d", largest_num, largest_count);
}
