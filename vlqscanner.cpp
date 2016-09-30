#include "vlqscanner.h"
#include <QList>

VLQScanner::VLQScanner(QByteArray &ba) {
    QList<int> parsed;
    bool parsing = true;
    int index = 0;
    while((ba.length() > 0) && (index < 4) && parsing) {
        QByteArray sVal = ba.left(1);
        uchar tmpVal = uchar(sVal.at(0));
        if((tmpVal & 0x80) || parsing) {
            ba = ba.right(ba.length() - 1);
            parsed.append(tmpVal & 0x7F);
            if(!(tmpVal & 0x80)) break;
            index++;
        } else {
            break;
        }
    }
    value = 0;
    if(parsed.length() > 0) {
        for(index = parsed.length(); index > 0; index--) {
            value += parsed.at(index - 1) << ((index - 1) * 7);
        }
    }
}
