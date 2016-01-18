#ifndef USER_H
#define USER_H
//#include <string>
#include <QString>
//#include <QTime>

class user
{
public:
    user();
    ~user();
//    QString username;
//    uint m;
//    uint p;
//    QString eidNum;

    char *id;
    short len_id;
    char *eIDNum;
    short len_eidnum;
    char *m;
    short len_m;
    char *p;
    short len_p;


    QString Ti;  //QTime::toString();
};

#endif // USER_H
