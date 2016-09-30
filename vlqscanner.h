#ifndef VLQSCANNER_H
#define VLQSCANNER_H

#include <QByteArray>

class VLQScanner {
public:
    VLQScanner(QByteArray &ba);
    u_int64_t translated() { return value; }

private:
    u_int64_t value;
};

#endif // VLQSCANNER_H
