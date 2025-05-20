#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main() {

    Process processes[5];
    create_process(processes, 5, 42);

    return 0;
}