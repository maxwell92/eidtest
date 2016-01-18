#ifndef REG_H
#define REG_H

#include <QString>

class reg
{
public:
    reg();
    char *name;
    short len_name;
    char *eIDNum;
    short len_eidnum;
    char *m;
    short len_m;
    char *guid;
    short len_guid;

    QString reg_time;
    char *rtime;
    short len_time;

    char *y;
    int len_y;
};

#endif // REG_H
