#include "ba32tobe.h"

BA32toBE::BA32toBE(QByteArray ba) {
    QByteArray tmp = ba.left(4);
    result = uchar(tmp.at(0)) * 0x1000000;
    result += uchar(tmp.at(1)) * 0x10000;
    result += uchar(tmp.at(2)) * 0x100;
    result += uchar(tmp.at(3));
}

