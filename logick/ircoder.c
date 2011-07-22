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
 *   |header | 0 | 1  | 0 | 1  | stop|
 *   |  1110 | 10| 100| 10| 100| 1   | == 11101010 01010010 == 0xEA 0x52
 */

int code2ir_shot(uint8_t *code, uint8_t *result, int size_of_bites)
{
  int x,y;
  *result=y=0;
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
  result[y]|=1<<(7-x);

  return 0;
}

/*
 * Convert IR sequence to real code
 *
 * Package:
 *  1 1 1 0 -- HEADER
 *  1 0     -- Logick "0"
 *  1 0 0   -- Logick "1"
 *
 *  Example:
 *   code == 0xEA 0x50 == 11101010 01010000
 *  ircode
 *   |  1110 | 10| 100| 10| 100| stop|
 *   |header | 0 | 1  | 0 | 1  |     | == 0x05
 */

int ir_shot2code(uint8_t *ircode, uint8_t *code)
{
  int x,y;
  *code=y=0;
  x=8;
  // FIXME maybe header isn't exist.
  int a,b;
  int one,null,head;
  a=b=0;
  null=head=one=0;
  int max=100;
  while(max--){
    int byte=(ircode[a]>>(7-b))&1;
    if(byte == 1){
      if(one==1){
        if(null==0){
          head=1;//header, drop one byte
        }else if((null>1)){
          if(head==1){
            head=0;
            continue;
          }
            code[y]|=1<<x;
            if(x--==0){
              x=7;
              code[++y]=0;
            }
        }else{
          if(x--==0){
            x=7;
            code[++y]=0;
          }
        }
      }
      null=0;
      one=1;
    }else{
      null++;
    }
    if((one==1) && (null>2)){
      break;
    }
    if(++b>=8){
      b=0;
      a++;
    }
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
  //printf("%llx\n", *result);
  assert(*result== 0xa8ea);
  ir_shot2code(rcode, code);
  assert(*((uint64_t*)code) == 0x00);
  //printf("%llx\n", *((uint64_t*)code));


  st=0x0000000000000005ll;
  code2ir_shot(code, rcode, 4);
  assert(*result== 0x52ea);
  ir_shot2code(rcode, code);
  assert(*((uint64_t*)code) == 0x05<<4);// Four byte

  st=0x0000000000000055ll;
  code2ir_shot(code, rcode, 8);
  assert(*result == 0x809452ea);
  ir_shot2code(rcode, code);
  assert(*((uint64_t*)code) == 0x55);

  st=0x87654321ll;//FIXME
  code2ir_shot(code, rcode, 32);
  assert(*result == 0x49554aa9a42455e9);
  //printf("%llx\n", *result);
  ir_shot2code(rcode, code);
  assert(*((uint64_t*)code) == 0x21436587);
  //printf("%llx\n", *((uint64_t*)code));
  // FIXME
  // code2ir_shot -- broken if bit_size > 32

  printf("All test success!\n");

  return 0;
}
#endif /*_MAIN_*/
