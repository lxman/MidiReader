#include "generator.h"
#include "converter.h"
#include <QDebug>

Generator::Generator(QList<TrkChunk *> tracks, u_int64_t tick_resolution) {
	int trkNum = 0;
	foreach (TrkChunk *trkChunk, tracks) {
		qDebug() << "Events for track #" << trkNum;
		QList<int> trkNumList = trkChunk->getTrackNums();
		foreach (int trkInt, trkNumList) {
			qDebug() << "Track #" << trkNum << " contains a data track for " << trkInt;
			DebugEvents(trkChunk, trkInt, tick_resolution);
		}
		qDebug() << "\n";
		trkNum++;
	}
}

void Generator::DebugEvents(TrkChunk *trkChunk, int track, u_int64_t resolution) {
	Converter cvt;
	foreach (Event *e, trkChunk->getTrack(track)->Events()) {
		qDebug() << "\tEvent type: " << cvt.EventTypeToString(e->getType()) << ", tick: " << QString::number(e->getTicks()) << ", bars: " << QString::number((e->getTicks() / resolution) / 2);
		if((e->getType() == note_on) || (e->getType() == note_off) ||
		   (e->getType() == poly_key)) {
			qDebug() << "\t\tNote: " << e->getName() << ", octave " << e->getOctave() << ", velocity " << e->getVelocity();
		}
		if(e->getType() == cnt_change) {
			qDebug() << "\t\tController: " << cvt.ControllerToString(e->getVal1()) << ", value " << QString::number(e->getVal2());
		}
		if(e->getType() == pgm_change) {
			qDebug() << "\t\tInstrument: " << cvt.ProgramChangeToString(e->getVal1());
		}
		if(e->getType() == port_sel) {
			qDebug() << "\t\tPort: " << QString::number(e->getVal1());
		}
	}
}

