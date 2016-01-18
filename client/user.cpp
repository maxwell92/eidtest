#include "user.h"
#include <malloc.h>

user::user()
{
    len_id = 20;
    id = (char *)malloc(len_id*sizeof(char));
    memset(id,'\0',len_id);

    len_eidnum = 9;
    eIDNum = (char *)malloc(len_eidnum*sizeof(char));
    memset(eIDNum,'\0',9);

    len_m = 3;
    m = (char *)malloc(len_m*sizeof(char));
    memset(m,'\0',2);

    len_p = 7;
    p = (char *)malloc(len_p*sizeof(char));
    memset(p,'\0',len_p);

}

user::~user()
{

}
