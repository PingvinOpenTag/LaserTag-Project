#include "usbtty.h"

#ifndef BUFFSIZE
 #warning Please, set BUFFSIZE for stdout buffer.
 #define BUFFSIZE 100
#endif

char buffout[BUFFSIZE];
int blast=0;
int bcur=0;
void bchar(char c)
{
 	buffout[bcur]=c; 
	if(bcur++>=BUFFSIZE)
		bcur=0;
	if(blast == bcur)
		if(blast++>=BUFFSIZE)
			blast=0;
}
char _bchar_pop()
{
	char out;
	if(bcur==blast)
		return 0;
	
	out = buffout[blast];
	if(blast++>=BUFFSIZE)
		blast=0;
	if(out==0) out++;
	return out;
}

int bchar_put(char ch, FILE* file)
{
	bchar(ch);
	return 0;
}

int outs(char* str)
{
	int len = strlen(str);
	int i;
	for(i=0; i<len; i++)
		bchar(str[i]);
}

