#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define FMT_STR_SIZE 40960

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

int64_t get_date_millis() {
  struct timeval time;
  gettimeofday(&time, NULL);
  int64_t s1 = (int64_t)(time.tv_sec) * 1000;
  int64_t s2 = (time.tv_usec / 1000);
  return s2;
}


int64_t get_timestamp() {
  struct timeval time;
  gettimeofday(&time, NULL);
  int64_t s1 = (int64_t)(time.tv_sec) * 1000;
  int64_t s2 = (time.tv_usec / 1000);
  return s1+s2;
}


signed char* fmt_str1(signed char* format_str, signed char* arg1)
{   
    static signed char va_fmt_str1[FMT_STR_SIZE];
    sprintf(va_fmt_str1, format_str, arg1);
    return va_fmt_str1;
}

signed char* fmt_str2(signed char* format_str, signed char* arg1, signed char* arg2)
{
    static signed char va_fmt_str2[FMT_STR_SIZE];
    sprintf(va_fmt_str2, format_str, arg1, arg2);
    return va_fmt_str2;
}

signed char* fmt_str3(signed char* format_str, signed char* arg1, signed char* arg2, signed char* arg3)
{
    static signed char va_fmt_str3[FMT_STR_SIZE];
    sprintf(va_fmt_str3, format_str, arg1, arg2, arg3);
    return va_fmt_str3;
}

signed char* fmt_str4(signed char* format_str, signed char* arg1, signed char* arg2, signed char* arg3, signed char* arg4)
{
    static signed char va_fmt_str4[FMT_STR_SIZE];
    sprintf(va_fmt_str4, format_str, arg1, arg2, arg3, arg4);
    return va_fmt_str4;
}

signed char* fmt_str5(signed char* format_str, signed char* arg1, signed char* arg2, signed char* arg3, signed char* arg4, signed char* arg5)
{
    static signed char va_fmt_str5[FMT_STR_SIZE];
    sprintf(va_fmt_str5, format_str, arg1, arg2, arg3, arg4, arg5);
    return va_fmt_str5;
}
