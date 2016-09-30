#ifndef HEADERCHUNK_H
#define HEADERCHUNK_H

#include <QByteArray>

class HeaderChunk {
public:
    HeaderChunk(QByteArray ba);
    bool isValid() { return valid; }
    bool smpteFormat() { return isSmpte; }
    int format() { return songFormat; }
    int numTracks() { return nTracks; }
    int division() { return timeDivision; }
    int tpfValue() { return tpf; }

private:
    bool valid;
    bool isSmpte;
    int songFormat;
    int nTracks;
    int timeDivision;
    int tpf;
};

#endif // HEADERCHUNK_H
