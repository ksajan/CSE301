#include <stdlib.h>
#include <stdio.h>
 
#define COMMAND_TO_RUN "last -f /var/run/utmp"
 
int main(int argc, char **argv) {
        printf("Running ps with system\n");
        system(COMMAND_TO_RUN);
        printf("Done.\n");
        return 0;
}
