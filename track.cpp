#include "track.h"

Track::Track() {

}

void Track::AddEvent(u_int64_t delta, EventType et, QByteArray &ba) {
	events.append(new Event(delta, et, ba));
}
