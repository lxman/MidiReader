#include "headerchunk.h"

#include <QByteArray>
#include "ba32tobe.h"
#include "ba16tobe.h"

HeaderChunk::HeaderChunk(QByteArray ba) {
    QByteArray test = ba.left(4);
    if(test != "MThd") {
        valid = false;
        return;
    }
    int length = BA32toBE(ba.mid(4, 4)).translated();
    if(length != 6) {
        valid = false;
        return;
    }
    songFormat = BA16toBE(ba.mid(8, 2)).translated();
    nTracks = BA16toBE(ba.mid(10, 2)).translated();
    QByteArray d = ba.mid(12, 2);
    if(!(d.at(0) & 0x8000)) {
        timeDivision = BA16toBE(d).translated();
        tpf = 1;
        isSmpte = false;
    } else {
        QByteArray tmp = d;
        tmp[0] = tmp.at(0) ^ 0x80;
        QByteArray smpte = d;
        smpte[1] = smpte.at(0);
        smpte[0] = 0;
        timeDivision = -(32 - smpte[1]);
        QByteArray tpfV = d;
        tpfV[0] = 0;
        tpf = tpfV[1];
        isSmpte = true;
    }
    valid = true;
}

