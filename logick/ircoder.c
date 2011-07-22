#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/*
 * Convert real code to IR sequence
 *
 * Package:
 *  1 1 1 0 -- HEADER
 *  1 0     -- Logick "0"
 *  1 0 0   -- Logick "1"
 *
 *  Example:
 *   code == 0x05 -- 0b0101
 *  ircode:
 *   |header | 0 | 1  | 0 | 1  |
 *   |  1110 | 10| 100| 10| 100| == 11101010 01010000 == 0xEA 0x50
 */

int code2ir_shot(uint8_t *code, uint8_t *result, int size_of_bites)
{
  int i,x,y;
  *((uint64_t*)result)=y=0;
  result[0]=0xe0;// 1110 0000 -- HEADER
  x=4;

  while(size_of_bites--){
    int a,b;
    uint8_t times;
    times=2;
    a=size_of_bites/8;
    b=size_of_bites%8;

    if(((code[a]>>b)&1) == 1)
      times++;

    result[y]|=1<<(7-x);
    while(times--)
      if(++x>=8)
        result[++y]=x=0;
  }

  return 0;
}

#ifdef _MAIN_
#include <assert.h>
/* Byte reverse output.
 */
int printIRcode(uint8_t *ircode, size_t size)
{
  uint8_t i=0;
  printf("0x");
  size/=8;
  while(size--){
    printf("%2.2x", ircode[i++]);
  }
  printf("\n");
  return 0;
}

int main(void)
{
  uint8_t rcode[8];
  uint64_t st;

  uint8_t  *code   = (uint8_t*)  &st;
  uint64_t *result = (uint64_t*) &rcode;

  st=0x0000000000000000ll;
  code2ir_shot(code, rcode, 4);
  assert(*result== 0xa0ea);

  st=0x0000000000000005ll;
  code2ir_shot(code, rcode, 4);
  assert(*result== 0x50ea);

  st=0x0000000000000055ll;
  code2ir_shot(code, rcode, 8);
  assert(*result == 0x9452ea);

  st=0x0987654321ll;
  code2ir_shot(code, rcode, 40);
  assert(*result == 0x522a29495552a9ea);

  printf("All test success!\n");

  return 0;
}
#endif /*_MAIN_*/
