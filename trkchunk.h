#ifndef TRKCHUNK_H
#define TRKCHUNK_H

#include <QByteArray>
#include <QList>
#include "event.h"

class TrkChunk {
public:
    TrkChunk(QByteArray ba);

private:
    QByteArray *data;
    int delta_time;
    QList<Event *> events;
};

#endif // TRKCHUNK_H
