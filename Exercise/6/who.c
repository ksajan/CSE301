#include <utmp.h>
#include <utmpx.h>
#include <stdio.h>
#include <sys/time.h>
 
#define UTMP_FILENAME "/var/run/utmp"
 
int main()
{
 
        struct utmp record;
        FILE *fd = fopen(UTMP_FILENAME, "r");
 
        if (fd == NULL) {
                perror(UTMP_FILENAME);
                return 1;
        }
        while (fread(&record, sizeof record, 1, fd) != 0) {
                printf("%s\t: %s\t: %s\t  %d\n", record.ut_line, record.ut_user, record.ut_id, record.ut_tv.tv_sec);
        }
        return 0;    }
