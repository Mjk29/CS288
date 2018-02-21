#include <stdio.h>

int convert();


int main()
{

    int k;
    int c;
    int n = 12345;



    int x =  12345;

     int mask = 0xFF0F;

    int masked = x & mask;


    // int bin = convert(x);


printf("    %d\n", (x/1) % 10);
printf("   %d \n", (x/10) % 10);
printf("  %d  \n", (x/100) % 10);
printf(" %d   \n", (x/1000) % 10);
printf("%d    \n", (x/10000) % 10);

printf("%d\n", (123456789 & 0000111111  ));




// printf("%d\n", mask);
// printf("%08x\n", mask);
// printf("%d\n", masked);
// printf("%d\n", bin);




 // for (c = 31; c >= 0; c--)
 //  {
 //    k = n >> c;
 
 //    if (k & 1)
 //      printf("1");
 //    else
 //      printf("0");
 //  }

printf("\n");


}


int convert(int dec)

{

    if (dec == 0)

    {

        return 0;

    }

    else

    {

        return (dec % 2 + 10 * convert(dec / 2));

    }

}





    // unsigned int x = 3, y = 1, sum, carry;
    // sum = x ^ y; // x XOR y
    // carry = x & y; // x AND y
    // while (carry != 0) {
    //     carry = carry << 1; // left shift the carry
    //     x = sum; // initialize x as sum
    //     y = carry; // initialize y as carry
    //     sum = x ^ y; // sum is calculated
    //     carry = x & y; /* carry is calculated, the loop condition is 
    //                       evaluated and the process is repeated until 
    //                       carry is equal to 0.
    //                     */
    // }
    // printf("%d\n", sum); // the program will print 4
    // return 0;
