#ifndef CITIZEN_H
#define CITIZEN_H

class citizen
{
public:
    citizen();
//private:

    char *idnum;
    short len_idnum;
    char *eIDNum;
    short len_eidnum;
    char *addr;
    short len_addr;
    char *ins;
    short len_ins;

    char *age;
    short len_age;
    char *tele;
    short len_tele;
    char *gen;
    short len_gen;
    char *name;
    short len_name;
    char *dep;
    short len_dep;
};

#endif // CITIZEN_H
