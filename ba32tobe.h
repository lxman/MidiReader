#ifndef BA32TOBE_H
#define BA32TOBE_H

#include <QByteArray>

class BA32toBE {
public:
    BA32toBE(QByteArray ba);
    int translated() { return result; }

private:
    int result;
};

#endif // BA32TOBE_H
