#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <stddef.h>
//#define DEBUG

int main(int argc, char* argv[])
{
    if (argc!=3) {
        printf("Please pass two files to add\n");
        exit(EXIT_FAILURE);
    }

    FILE* pFile1 = fopen(argv[1],"r");
    FILE* pFile2 = fopen(argv[2],"r");

    uint8_t numBuf1[4], numBuf2[4];
    uint32_t num1, num2;

    fread(numBuf1, 1, 4, pFile1); // 00 05 00 00
    fread(numBuf2, 1, 4, pFile2); // 78 00 00 00

    uint32_t* pNum1 = reinterpret_cast<uint32_t*>(numBuf1);
    uint32_t* pNum2 = reinterpret_cast<uint32_t*>(numBuf2);
#ifdef DEBUG
    printf("num1 in little endian = %#.8x\n", *pNum1);
    printf("num2 in little endian = %#.8x\n", *pNum2);
#endif
    num1 = htonl(*pNum1);
    num2 = htonl(*pNum2);

#ifdef DEBUG
    printf("num1 in big endian = %#.8x\n", num1);
    printf("num2 in big endian = %#.8x\n", num2);
#endif
    uint32_t sum = num1 // 00 00 05 00
                   + num2; // 00 00 00 78

    printf("%d(%#x) + %d(%#x) = %d(%#x)\n",num1,num1,num2,num2,sum,sum);


    fclose(pFile1);
    fclose(pFile2);
    return 0;
}
