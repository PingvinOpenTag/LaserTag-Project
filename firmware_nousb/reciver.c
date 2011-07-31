#include <stdint.h>
#include <avr/io.h>
#include "reciver.h"
#include "support.h"

uint8_t recv[MSGMAXLEN*SENSORS]; // 2 -- bytes on messag; 8 -- IR sensors
uint8_t cur_bit[SENSORS];

uint8_t recv_mask[MSGMAXLEN];

enum{
  CUR_NONE,
  CUR_ONES,
  CUR_ZERO
};

uint8_t curstate[SENSORS];//CUR_NONE;
uint8_t curones[SENSORS];
uint8_t curzeros[SENSORS];

int recv_initialize()
{
  uint8_t i;
  for(i=0;i<SENSORS; i++){
    curstate[i]=CUR_NONE;
  }
  for(i=0;i<MSGMAXLEN; i++){
    recv_mask[i]=0;
  }
  // RECIVER BIT (from multiplexor)
  DDRBIT(B, 5, 0);
}
// TODO: XXX: FIXME:
//  it use many constant. It recive signal from Sender if Tick_Sender == Tick_Reciver*4
int recv_iteration(){

    uint8_t i;
    // PORTB ....XXX.  -- XXX -- address for multiplexsor
    PORTB=(PORTB & (~(7<<1))) | (0<<1);

    for(i=0;i<SENSORS;i++){
        char bit;
        PORTB=((PORTB & (~(7<<1))) | (i<<1));
        //_delay_us(10);
        //bit=!((PINB>>5)&1);
        bit=!((PINB>>5)&1);
        switch(curstate[i]){
          case CUR_NONE:
            if(bit==1){
              curones[i]=1;
              curzeros[i]=0;
              curstate[i]=CUR_ONES;
              cur_bit[i]=0; // it is a new message
              // whitout start bit. If star bit exist,
              // see below.
            }
            break;
          case CUR_ONES:
            if(bit==0){
              if(curones[i]>=9){// it is a START bit (1110). We need drop first bit (zero bit)
                curstate[i]=CUR_NONE; // Drop first bit.
                recv[i*2]=0;
                recv[i*2+1]=0;
              }else{
                curzeros[i]=1;
                curstate[i]=CUR_ZERO;
              }
            }else{
              curones[i]++;
            }
            break;
          case CUR_ZERO:
            if(bit==1){
              if(cur_bit[i]>=16){
                // BIT(B, 0, 1);
                //false
              }else{
                if(curzeros[i]>=7){
                  BIT(B, 4, 1);
                  if(cur_bit[i]<8){
                    recv[i*2]   |= (1<<(7 -cur_bit[i]));
                  }else{
                    recv[i*2+1] |= (1<<(15-cur_bit[i]));
                  }
                }else{
                  BIT(B, 4, 0);
                }
                cur_bit[i]++;
              }
              curzeros[i]=0;
              curones[i]=1;
              curstate[i]=CUR_ONES;
            }else{
              curzeros[i]++;
              if(curzeros[i]>15){
                cur_bit[i]=16;
                curstate[i]=CUR_NONE;
              }
#if 1 // for debug
              if(curzeros[i]>15){
                BIT(B, 0, 0);
                BIT(B, 0, 1);
                BIT(B, 0, 0);
                BIT(B, 0, 1);
                uint8_t x;
                for(x=0;x<8;x++){
                  BIT(B, 4, 0);
                  uint8_t b = (recv[i*2]>>(7-x))&1;
                  //uint8_t b = (0x55>>(7-x))&1;
                  BIT(B, 0, b);
                  BIT(B, 4, 1);
                }
                BIT(B, 0, 0);
                BIT(B, 0, 1);
                BIT(B, 0, 0);
                BIT(B, 0, 1); 
                for(x=0;x<8;x++){
                  BIT(B, 4, 0);
                  uint8_t b = (recv[i*2+1]>>(7-x))&1;
                  BIT(B, 0, b);
                  BIT(B, 4, 1);
                }
              }
#endif
            }
            break;
        }
    }
}
