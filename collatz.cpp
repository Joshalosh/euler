#include <iostream>

int main()
{
    int largest_count = 0;
    int largest_num = 0;

    for(int index = 2; index < 1000000; index++)
    {
        int num = index;
        int count = 1;
        while(num != 1)
        {
            if(num == largest_num)
            {
                count += largest_count - 1;
                break;
            }
            if(num % 2 == 0)
            {
                num /= 2;
            }
            else
            {
                num *= 3;
                num += 1;
            }
            count++;
        }

        if(count > largest_count)
        {
            largest_count = count;
            largest_num = index;
        }

        //printf("\nIndex:%d.  Count: %d", index, count);
    }

    printf("\nLargest number: %d   Largest Count: %d", largest_num, largest_count);
}
