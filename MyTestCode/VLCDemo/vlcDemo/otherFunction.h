
#include "vlc/vlc.h"

extern libvlc_exception_t ex;
extern libvlc_instance_t * inst;
extern libvlc_media_player_t *mp;
extern libvlc_media_t *m;

void raise(libvlc_exception_t * ex);



char *W2C(const wchar_t *pw , char *pc);
  
char *wstr2cstr(const wchar_t *pwstr , char *pcstr, size_t len);