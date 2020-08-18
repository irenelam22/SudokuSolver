
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./common/unit.h"
#include "./libcs50/counters.h"

int main(const int argc, char* argv[]){
unit_t* array[81];

for ( int i = 1; i < 82; i++){
    unit_t* unit = unit_new(i, 1);
    for ( int i = 1; i < 10; i++){
        possibles_add(unit, i);
    }
    array[i-1] = unit;
}

for (int i = 1; i < 82; i++){
    print_unit(array[i]);
}

printf("Remove from item 81\n");
bool val = possibles_remove(array[81], 2);
printf("Success? %d\n", val);
print_unit(array[81]);

}