#include "event.h"
#include <QtMath>
#include "ba32tobe.h"
#include <QDebug>

Event::Event(u_int64_t delta, EventType t, QByteArray &ba) {
	et = t;
	delta_time = delta;
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
	if(ba.length() > 0) val1 = (uchar)ba.at(0);
	if(ba.length() > 1) val2 = (uchar)ba.at(1);
	qDebug() << "Delta time " << delta_time;
	qDebug() << "Event type " << et;
	if(ba.length() > 0) qDebug() << "Data 1 " << val1;
	if(ba.length() > 1) qDebug() << "Data 2 " << val2;
	qDebug() << "\n";

//	QByteArray *tmp = new QByteArray(ba.length());
//	for(int index = 0; index < ba.length(); index++) tmp[index] = ba.at(index);
//	data = tmp->data();
}
