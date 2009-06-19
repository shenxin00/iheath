
#include "stdafx.h"
#include "vlc/vlc.h"


libvlc_exception_t ex;
libvlc_instance_t * inst = NULL;
libvlc_media_player_t *mp = NULL;
libvlc_media_t *m = NULL;

void raise(libvlc_exception_t * ex)
{
    if (libvlc_exception_raised (ex))
    {
         fprintf (stderr, "[test]error: %s\n", libvlc_exception_get_message(ex));
         exit (-1);
    }
}


char *W2C(const wchar_t *pw , char *pc)
{
      *pc++ = *pw >> 8 ;
      *pc = *pw ;
      return 0 ;
}
  
char *wstr2cstr(const wchar_t *pwstr , char *pcstr, size_t len)
{
	char *ptemp = pcstr ;
      if(pwstr!=NULL && pcstr!=NULL)
      {
        
          size_t wstr_len = wcslen(pwstr) ;
          len = (len > wstr_len ) ?    wstr_len : len ;
      while( len -- > 0)
      {

          W2C(pwstr , pcstr);
          pwstr++ ;
          pcstr +=2 ;    
      }
          *pcstr = '\0';
          return ptemp ;
      }
      return 0 ;
}    
