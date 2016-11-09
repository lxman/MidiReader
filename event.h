#ifndef METAEVENT_H
#define METAEVENT_H

#include <QByteArray>
#include <QString>
#include "globals.h"

class Event {
public:
	Event(u_int64_t nTicks, EventType t, QByteArray &ba);
	EventType getType() { return et; }
	void *getData() { return data; }
	int getVal1() { return val1; }
	int getVal2() { return val2; }
	u_int64_t getTicks() { return ticks; }
	int getOctave() { return nOctave; }
	QString getName() { return nName; }
	u_int8_t getVelocity() { return velocity; }

private:
	QByteArray TranslateNote(uchar data);
	u_int64_t ticks;
	EventType et;
	void *data;
	int val1;
	int val2;
	timeSig t_sig;
	kSig k_sig;
	int uSec_qn;
	int nOctave;
	QString nName;
	u_int8_t velocity;
};

#endif // EVENT_H
