#include "event.h"
#include <QtMath>
#include "ba32tobe.h"
#include "converter.h"

Event::Event(u_int64_t nTicks, EventType t, QByteArray &ba) {
	et = t;
	ticks = nTicks;
	Converter cvt;
	if(et == time_sig) {
		t_sig.num = (uchar)ba.at(0);
		t_sig.den = pow(2, (uchar)ba.at(1));
		t_sig.met = (uchar)ba.at(2);
		t_sig.note_rat = (uchar)ba.at(3);
	}
	if(et == key_sig) {
		k_sig.key = ba.at(0);
		k_sig.major = ((uchar)ba.at(1) == 0);
	}
	if(et == set_tempo) {
		QByteArray tmp = QByteArray(4, 0);
		tmp[1] = ba.at(0);
		tmp[2] = ba.at(1);
		tmp[3] = ba.at(2);
		uSec_qn = BA32toBE(tmp).translated();
	}
	if((et == note_on) || (et == note_off) ||
	   (et == poly_key)) {
		QByteArray tmp = TranslateNote(ba.at(0));
		nOctave = tmp.at(0);
		nName = cvt.NoteToString(tmp.at(1));
		velocity = ba.at(1);
	}
	if(ba.length() > 0) val1 = (uchar)ba.at(0);
	if(ba.length() > 1) val2 = (uchar)ba.at(1);
}

QByteArray Event::TranslateNote(uchar data) {
	QByteArray retValue = QByteArray(2, 0);
	int8_t octave = data % 12;
	data = data - ((data / 12) * 12);
	octave -= 1;
	retValue[0] = octave;
	retValue[1] = data;
	return retValue;
}
