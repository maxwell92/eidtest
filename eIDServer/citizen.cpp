#include "citizen.h"
#include <malloc.h>
#include <QString>

citizen::citizen()
{

    len_idnum = 19;
    idnum = (char *)malloc(len_idnum*sizeof(char));
    memset(idnum,'\0',len_idnum);

    len_eidnum = 9 ;
    eIDNum = (char *)malloc(len_eidnum*sizeof(char));
    memset(eIDNum,'\0',len_eidnum);

    len_addr = 21;
    addr = (char *)malloc(len_addr*sizeof(char));
    memset(addr,'\0',len_addr);

    len_ins = 11;
    ins = (char *)malloc(len_ins*sizeof(char));
    memset(ins,'\0',len_ins);

    len_age = 3;
    age = (char *)malloc(len_age*sizeof(char));
    memset(age,'\0',len_age);

    len_tele = 14;
    tele = (char *)malloc(len_tele*sizeof(char));
    memset(tele,'\0',len_tele);

    len_gen = 2;
    gen = (char *)malloc(len_gen*sizeof(char));
    memset(gen,'\0',len_gen);

    len_name = 21;
    name = (char *)malloc(len_name*sizeof(char));
    memset(name,'\0',len_name);

    len_dep = 21;
    dep = (char *)malloc(len_dep*sizeof(char));
    memset(dep,'\0',len_dep);


}
