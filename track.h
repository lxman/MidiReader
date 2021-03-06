#ifndef TRACK_H
#define TRACK_H

#include <QList>
#include "event.h"

class Track {
public:
	Track();
	void AddEvent(u_int64_t delta, EventType et, QByteArray &ba);
	QList<Event *> Events() { return events; }

private:
	QList<Event *> events;
};

#endif // TRACK_H
