#include "logger.h"

logger::logger()
{
    len_name = 20;
    name = (char *)malloc(len_name*sizeof(char));
    memset(name,'\0',len_name);

    len_eidnum = 9;
    eIDNum = (char *)malloc(len_eidnum*sizeof(char));
    memset(eIDNum,'\0',len_eidnum);

    len_m = 3;
    m = (char *)malloc(len_m*sizeof(char));
    memset(m,'\0',len_m);

    len_guid = 129;
    guid = (char *)malloc(len_guid*sizeof(char));
    memset(guid,'\0',len_guid);

    len_time = 9;
    rtime = (char *)malloc(len_time*sizeof(char));
    memset(rtime,'\0',len_time);

    len_y = 7;
    y = (char *)malloc(len_y*sizeof(char));
    memset(y,'\0',len_y);
}
