#ifndef METAEVENT_H
#define METAEVENT_H

#include <QByteArray>
#include "globals.h"

class Event {
public:
	Event(u_int64_t delta, EventType t, QByteArray &ba);
	EventType getType() { return et; }
	void *getData() { return data; }
	int getVal1() { return val1; }
	int getVal2() { return val2; }

private:
	u_int64_t delta_time;
	EventType et;
	void *data;
	int val1;
	int val2;
	timeSig t_sig;
	kSig k_sig;
	int uSec_qn;
};

#endif // EVENT_H
