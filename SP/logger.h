#ifndef LOGGER_H
#define LOGGER_H
#include <QString>

class logger
{
public:
    logger();
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

    char *y;   //用来保存hash函数的返回值
    int len_y;
};

#endif // LOGGER_H
