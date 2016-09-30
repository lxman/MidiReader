#include "ba16tobe.h"

BA16toBE::BA16toBE(QByteArray ba) {
    result = uchar(ba.at(0)) * 0x100;
    result += uchar(ba.at(1));
}

