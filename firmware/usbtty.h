#include <stdio.h>
// óÐÏÓÏÂ ×Ù×ÏÄÁ ÓÉÍ×ÏÌÁ (ÉÓÐÏÌØÚÕÅÔÓÑ printf)
int bchar_put(char ch, FILE* file);

// óìõöåâîùå æõîëãéé 
char _bchar_pop();
	
#define USB_TTY_REQ( type )		\
	if(rq->bRequest == type)			\
	{															\
		int i=0;										\
		char ch=0;									\
		for(i=0; ( ch=_bchar_pop() ) && ( i<REPBUFF ); i++) \
			replyBuf[i] = ch;					\
		return i;										\
	}
