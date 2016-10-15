#ifndef TRKCHUNK_H
#define TRKCHUNK_H

#include <QByteArray>
#include <QList>
#include <QMap>
#include "event.h"
#include "track.h"

class TrkChunk {
public:
	TrkChunk(QByteArray ba);

private:
	void AddEvent(int chan, u_int64_t delta, EventType et, QByteArray &ba);

	QByteArray *data;
	int delta_time;
	QMap<int, Track *> tracks;
};

#endif // TRKCHUNK_H
