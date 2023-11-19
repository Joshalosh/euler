
#include<stdlib.h>
#include<stdio.h>

struct Placement
{
    int  value;
    bool is_in_use;
    bool completed_first_position;
};

#define PLACEMENT_COUNT 3
static struct Placement *InitPlacements()
{
    struct Placement *result = (Placement *)malloc(PLACEMENT_COUNT * sizeof(struct Placement));
    
    for (int i = 0; i < PLACEMENT_COUNT; i++) {
        result[i].value                    = i;
        result[i].is_in_use                = false; 
        result[i].completed_first_position = false;
    }

    return result;
}

int main()
{
    struct Placement *array = InitPlacements();

    for (int first_placement = 0; first_placement < PLACEMENT_COUNT; first_placement++) {
        array[first_placement].is_in_use = true;
        int index = 1;
        while (index < PLACEMENT_COUNT) {
            Placement dummy_placement = {};
            dummy_placement.value = INT_MAX;
            Placement *smallest_available_placement = &dummy_placement;
            for(int j = 0; j < PLACEMENT_COUNT; j++) {
                if (!array[j].is_in_use && array[j].value < smallest_available_placement->value) {
                    smallest_available_placement = &array[j];
                }
            }
            array[index] = *smallest_available_placement;
            smallest_available_placement->is_in_use = true;
            index++;
        }

        for (int i = 0; i < PLACEMENT_COUNT; i++) {
            printf("%d ", array[i].value);
            array[i].is_in_use = false;
        }
        printf("\n");
    }


    // Free the memory
    free(array);

    return 0;
}
