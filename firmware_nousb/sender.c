#include <stdint.h>
//#include <stddef.h>
#include <avr/io.h>
#include <avr/power.h>

#include "support.h"

#include "sender.h"

static uint8_t send_msg[8];
static uint8_t send_itr=8;
static uint8_t send_bititr=7;
static uint8_t send_length=0;

int send_iteration()
{
    if(send_is_freely()!=0){
      if((send_msg[send_itr]>>send_bititr)&1){
          T0_ON();
      }else{
          T0_OFF();
      }

      if(send_bititr--==0){
        send_itr++;
        send_bititr=7;
      }
    }
    if(send_is_freely()==0){
      T0_OFF();
      power_timer0_disable();
    }
    return 0;
}

int send_set_message(uint8_t *msg, uint8_t count)
{
  // It needed ?
  //if(send_is_freely!=0)
  //  return send_is_freely;

  send_length=count;
  while(count--){
    send_msg[count]=msg[count];// FIXME: memcpy
  }
  send_itr=0;
  power_timer0_enable();

  return 0;
}

int send_is_freely()
{
  if(send_itr>=send_length){
    return 0;
  }
  return 1;
}
