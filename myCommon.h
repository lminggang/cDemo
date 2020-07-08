#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

signed char* format_string(signed char* str, signed char* args [])
{
    static signed char variable_format_string[4096];
    strcpy(variable_format_string, str);
    for (signed char &i:args)
    {
        strcat(variable_format_string, i)
    }
    sprintf(variable_format_string, "%s/log.log", save_path);
}

void extend_folders(char *path){
    if(access(path, 0)!=0){
        int len =(int )strlen(path);
        int position=-1;
        for(int i=len-1;i>=0;--i){
            if(path[i]=='/'){
                position=i;
                break;
            }
        }
        if(position==-1){
            mkdir(path, 0775);//防止相对路径
        }else{
            char *newpath=calloc((size_t)position,sizeof(char));
            extend_folders(strncpy(newpath,path,position));
            free(newpath);
            mkdir(path, 0775);
        }
    }
}

signed char* get_date()
{
    static signed char date[34];
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
    sprintf(date, "%4d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec);
    return date;
}

signed char* get_date_ymd()
{
    static signed char date_ymd[34];
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int year,month,day;
    year = 1900+timeinfo->tm_year;
    month = 1+timeinfo->tm_mon;
    day = timeinfo->tm_mday;
    sprintf(date_ymd, "%4d-%02d-%02d", year, month, day);
    return date_ymd;
}

signed char* get_date_hms()
{
    static signed char date_hms[34];
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int hour,min,sec;
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    sprintf(date_hms, "%02d:%02d:%02d", hour, min, sec);
    return date_hms;
}
