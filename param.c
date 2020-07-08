#include <stdio.h>
#include <string.h>

char * get_device_ip(char * dev)
{
   static char str[80];
   strcpy (str,"192.168.1.");
   strcat (str, dev);
   return str;
}


int main( int argc, char *argv[] )  
{

   for (int i = 1; i < argc; ++i)
   {
      /* code */
      printf("%s\n", argv[i]);
   }

   if( argc == 2 )
   {
      char dev[10];
      strcpy (dev, argv[1]);
      char * str;
      str = get_device_ip(dev);
      printf("%s\n", str);
   }
   else if( argc > 2 )
   {
      printf("Too many arguments supplied.\n");
   }
   else
   {
      printf("One argument expected.\n");
   }

   return 0;
   
}