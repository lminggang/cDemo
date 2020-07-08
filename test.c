#include<stdio.h>
#include<stdlib.h>

#include <sys/time.h>
/**
* @brief provide same output with the native function in java called
* currentTimeMillis().
*/
int64_t currentTimeMillis() {
  struct timeval time;
  gettimeofday(&time, NULL);
  int64_t s1 = (int64_t)(time.tv_sec) * 1000;
  int64_t s2 = (time.tv_usec / 1000);
  
  printf("1 - %ld\n", s1);
  printf("2 - %ld\n", s2);

  return s1 + s2;
}

int main()
{
    int64_t s = currentTimeMillis();
    printf("%ld \n", s);

    struct timeval  tv;
    gettimeofday(&tv, NULL);

    int64_t time_in_mill = 
         (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
    printf("%ld\n", time_in_mill);



    int a;
    char *str="2353000000000FA0";
    sscanf(str,"%x",&a);//%x为读入bai16进制数，大du小写均可。zhisscanf是从c字符串中读入变量。
    printf("%i \n",a);

    char hex_str[10];
    sprintf(hex_str, "%x", a);
    printf("%s \n", hex_str);

    return 0;
}
