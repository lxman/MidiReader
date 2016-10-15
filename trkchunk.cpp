#include "trkchunk.h"
#include "vlqscanner.h"
#include "globals.h"
#include <QDebug>

void TrkChunk::AddEvent(int chan, u_int64_t delta, EventType et, QByteArray &ba) {
	QList<int> keys = tracks.keys();
	if (!keys.contains(chan)) {
		tracks.insert(chan, new Track());
	}
	Track *curr = tracks.value(chan);
	curr->AddEvent(delta, et, ba);
}

TrkChunk::TrkChunk(QByteArray ba) {
	int runningStatus;
	data = new QByteArray(ba.length(), 0);
	for(int index = 0; index < ba.length(); index++) {
		(*data)[index] = ba.at(index);
	}
	while(data->length() > 0) {
		u_int64_t delta = VLQScanner(*data).translated();
		uchar test = (uchar)(*data->left(1).data());
		if(!(test & 0x80)) {
			test = runningStatus;
		} else {
			runningStatus = test;
			*data = data->right(data->length() - 1);
		}
		if((test & 0xF0) == 0xF0) {
			// Looks like a system common or system real-time message
			switch(test) {
			case 0xF0: {
				// System common or system realtime - needs to be analyzed further
				qDebug() << "System common or system realtime";
			}
				break;
			case 0xF2: {
				// Song position pointer
				qDebug() << "Song position pointer";
				*data = data->right(data->length() - 2);
			}
				break;
			case 0xF3: {
				// Song select
				qDebug() << "Song select";
				*data = data->right(data->length() - 1);
			}
				break;
			case 0xF6: {
				// Tune request
				qDebug() << "Tune request";
			}
				break;
			case 0xF7: {
				// End of exclusive
				qDebug() << "End of exclusive";
			}
				break;
			case 0xF8: {
				// Timing clock
				qDebug() << "Timing clock";
			}
				break;
			case 0xFA: {
				// Start
				qDebug() << "Start";
			}
				break;
			case 0xFB: {
				// Continue
				qDebug() << "Continue";
			}
				break;
			case 0xFC: {
				// Stop
				qDebug() << "Stop";
			}
				break;
			case 0xFE: {
				// Active sense
				qDebug() << "Active sense";
			}
				break;
			case 0xFF: {
				// This is a meta-event
				test = uchar(*data->left(1).data());
				QByteArray test2 = data->mid(1, 1);
				int len = uchar(*test2.data());
				QByteArray metaEventData = data->mid(2, len);
				*data = data->right(data->length() - (len + 2));
				int chan = -1;
				switch(test) {
				case 0x00:
					// Sequence number
					AddEvent(chan, delta, sequence_no, metaEventData);
					break;
				case 0x01:
					// Text event
					AddEvent(chan, delta, text, metaEventData);
					break;
				case 0x02:
					// Copyright notice
					AddEvent(chan, delta, copy_not, metaEventData);
					break;
				case 0x03:
					// Sequence/track name
					AddEvent(chan, delta, seq_name, metaEventData);
					break;
				case 0x04:
					// Instrument name
					AddEvent(chan, delta, inst_name, metaEventData);
					break;
				case 0x05:
					// Lyric
					AddEvent(chan, delta, text_lyric, metaEventData);
					break;
				case 0x06:
					// Marker
					AddEvent(chan, delta, text_mark, metaEventData);
					break;
				case 0x07:
					// Cue point
					AddEvent(chan, delta, cue_point, metaEventData);
					break;
				case 0x20:
					// MIDI channel prefix
					AddEvent(chan, delta, chan_prefix, metaEventData);
					break;
				case 0x21:
					// Port message
					AddEvent(chan, delta, port_sel, metaEventData);
					*data = data->right(data->length() - 2);
					break;
				case 0x2F:
					// End of track
					AddEvent(chan, delta, eot, metaEventData);
					break;
				case 0x51:
					// Set tempo
					AddEvent(chan, delta, set_tempo, metaEventData);
					break;
				case 0x54:
					// SMPTE offset
					AddEvent(chan, delta, smpte_offset, metaEventData);
					break;
				case 0x58:
					// Time signature
					AddEvent(chan, delta, time_sig, metaEventData);
					break;
				case 0x59:
					// Key signature
					AddEvent(chan, delta, key_sig, metaEventData);
					break;
				case 0x7F:
					// Sequencer specific meta-event
					AddEvent(chan, delta, seq_spec, metaEventData);
					break;
				default:
					qDebug() << "Discarding " << QString::number(test, 16);
					break;
				}
			}
				break;
			default:
				qDebug() << "Discarding " << QString::number(test, 16);
				break;
			}
		} else {
			int command = 0xF0 & test;
			u_int8_t channel = 0xF & test;
			command = command >> 4;
			command ^= 0x8;
//			*data = data->right(data->length() - 1);
			switch(command) {
			case 0: {
				// Note off
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, note_off, tmp);
			}
				break;
			case 1: {
				// Note on
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, note_on, tmp);
			}
				break;
			case 2: {
				// Polyphonic key pressure (Aftertouch)
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, poly_key, tmp);
			}
				break;
			case 3: {
				// Control change
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, cnt_change, tmp);
			}
				break;
			case 4: {
				// Program change
				QByteArray tmp = data->left(1);
				*data = data->right(data->length() - 1);
				AddEvent(channel, delta, pgm_change, tmp);
			}
				break;
			case 5: {
				// Channel pressure (Aftertouch)
				QByteArray tmp = data->left(1);
				*data = data->right(data->length() - 1);
				AddEvent(channel, delta, chan_press, tmp);
			}
				break;
			case 6: {
				// Pitch wheel change
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, pw_change, tmp);
			}
				break;
			default:
				qDebug() << "Discarding " << QString::number(test, 16);
				break;
			}
		}
	}
}

