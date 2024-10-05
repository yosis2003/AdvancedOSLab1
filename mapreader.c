#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#define CHARSBEINGREAD 1000


int main ()
{
    FILE* mapsFileDescriptor = fopen("/proc/self/maps", "r");
    char lineCurrentlyRead[CHARSBEINGREAD];
    struct rusage performanceStats;


    while (fgets(lineCurrentlyRead, CHARSBEINGREAD, mapsFileDescriptor))
    {
        printf("%s\n", lineCurrentlyRead);
    }


    getrusage(RUSAGE_SELF, &performanceStats);

    printf("%ld\n", performanceStats.ru_minflt);
    printf("%ld\n", performanceStats.ru_maxrss);
    printf("%ld\n", performanceStats.ru_majflt);
    printf("%ld\n", performanceStats.ru_inblock);
    printf("%ld\n", performanceStats.ru_oublock);
    printf("%ld\n", performanceStats.ru_minflt);
    printf("%ld\n", performanceStats.ru_utime.tv_usec);
    printf("%ld\n", performanceStats.ru_stime.tv_usec);

}