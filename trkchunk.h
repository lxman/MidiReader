#ifndef TRKCHUNK_H
#define TRKCHUNK_H

#include <QByteArray>
#include <QList>
#include <QMap>
#include <QFile>
#include "event.h"
#include "track.h"

class TrkChunk {
public:
	TrkChunk(int trkNum, QByteArray ba);
	QList<int> getTrackNums() { return tracks.keys(); }
	Track *getTrack(int tr) { return tracks.value(tr); }

private:
	void AddEvent(int chan, u_int64_t delta, EventType et, QByteArray &ba);
	void WriteMessage(QFile &f, u_int64_t delta, QString message, QByteArray *data, int len);

	QByteArray *data;
	int delta_time;
	QMap<int, Track *> tracks;
	QMap<int, u_int64_t> curr_tick;
	u_int64_t ticks = 0;
};

#endif // TRKCHUNK_H
