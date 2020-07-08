#include <stdio.h>

#include <time.h>

int main()
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int year,month,day,hour,min,sec;
    year = 1900+timeinfo->tm_year;
    month = 1+timeinfo->tm_mon;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    printf ( "当前时间:%4d-%02d-%02d %02d:%02d:%02d\n",year, month,day,hour,min,sec);
    return 0;
} 
