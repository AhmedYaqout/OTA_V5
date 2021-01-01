#include "STD_TYPES.h"
#include "I2A.h"
void my_reverse(u8 s[])
 {
     s32 i, j;
     char c;

     for (i = 0, j = myStrLen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 void itoa(s32 n, u8 s[])
 {
     s32 i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     my_reverse(s);
 }
 u32 myStrLen(u8 str[])
 {
 	u32 strlen = 0;
 	for(u32 i=0; str[i] != '\0'; i++)
 	{
 		strlen++ ;
 	}
 	return strlen+1;
 }
