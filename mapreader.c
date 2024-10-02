#include <stdlib.h>
#include <stdio.h>

#define CHARSBEINGREAD 1000




int main ()
{

    FILE* mapsFileDescriptor = fopen("/proc/self/maps", "r");
    int maxCharsFgets = CHARSBEINGREAD;

    char lineCurrentlyRead[CHARSBEINGREAD];


    while (fgets(lineCurrentlyRead, maxCharsFgets, mapsFileDescriptor))
    {
        printf("%s\n", lineCurrentlyRead);

    }



}