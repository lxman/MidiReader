#ifndef GENERATOR_H
#define GENERATOR_H

#include <QTimer>
#include <QList>
#include "track.h"
#include "trkchunk.h"
#include "globals.h"
#include "event.h"

class Generator {
	public:
		Generator(QList<TrkChunk *> tracks, u_int64_t tick_resolution);

	private:
		void DebugEvents(TrkChunk *trkChunk, int track, u_int64_t resolution);
		QTimer t;
};

#endif // GENERATOR_H
