#include "event.h"

Event::Event(u_int64_t delta, EventType t, QByteArray &ba) {
    et = t;
    delta_time = delta;
    data = ba.data();
}


