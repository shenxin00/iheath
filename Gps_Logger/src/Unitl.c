



void strcpy(UINT8* dst,UINT8* src)
{
	while(*src != 0){
	
		*dst++ = *src++;
		
	}
	*dst = 0;
	
	return;
}

UINT8 strcmp(UINT8* dst,UINT8* src)
{
	UINT8 ret=0;

	while((*src != 0)){
		ret = (*dst++ - *src++);
		
		if(ret !=0 ){
			return ret;
		}
	}
	
	return *dst - *src;
}




