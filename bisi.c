#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="This is a simple string";
  char * pch;
  pch = strstr (str,"string");
  if (pch != NULL)
    strncpy (pch,"stringg",6);
  puts (str);
  return 0;
}