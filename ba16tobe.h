#ifndef BA16TOBE_H
#define BA16TOBE_H

#include <QByteArray>

class BA16toBE {
public:
    BA16toBE(QByteArray ba);
    int translated() { return result; }

private:
    int result;
};

#endif // BA16TOBE_H
