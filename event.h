#ifndef METAEVENT_H
#define METAEVENT_H

#include <QByteArray>
#include "globals.h"

class Event {
public:
    Event(u_int64_t delta, EventType t, QByteArray &ba);
    EventType getType() { return et; }
    void *getData() { return data; }

private:
    u_int64_t delta_time;
    EventType et;
    void *data;
};

#endif // EVENT_H
