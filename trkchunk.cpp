#include "trkchunk.h"
#include "vlqscanner.h"
#include "globals.h"
#include <QDebug>

void TrkChunk::AddEvent(int chan, u_int64_t delta, EventType et, QByteArray &ba) {
	QList<int> keys = tracks.keys();
	if (!keys.contains(chan)) {
		tracks.insert(chan, new Track());
		curr_tick.insert(chan, 0);
	}
	Track *curr = tracks.value(chan);
	u_int64_t currTicks = curr_tick.value(chan);
	currTicks += delta;
	curr_tick.insert(chan, currTicks);
	curr->AddEvent(currTicks, et, ba);
}

void TrkChunk::WriteMessage(QFile &f, u_int64_t delta, QString message, QByteArray *data, int len) {
	ticks += delta;
	QString rtn = "\n";
	f.write(message.toLatin1());
	f.write(rtn.toLatin1());
	QString tmp;
	tmp = "Delta=";
	tmp.append(QString::number(ticks) + "\n");
	f.write(tmp.toLatin1());
	tmp = "";
	uchar tmp2 = 0;
	for(int x = 0; x < len; x++) {
		tmp2 = data->at(x);
		tmp.append(QString::number(tmp2));
		tmp.append(" ");
	}
	f.write(tmp.toLatin1());
	f.write(rtn.toLatin1());
}

TrkChunk::TrkChunk(int trkNum, QByteArray ba) {
	QFile f(QString("Track" + QString::number(trkNum) + ".txt"));
	f.open(QFile::WriteOnly);
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
				WriteMessage(f, delta, "System common or system realtime\n", data, 0);
			}
				break;
			case 0xF2: {
				// Song position pointer
				WriteMessage(f, delta, "Song position pointer\n", data, 2);
				*data = data->right(data->length() - 2);
			}
				break;
			case 0xF3: {
				// Song select
				WriteMessage(f, delta, "Song select", data, 1);
				*data = data->right(data->length() - 1);
			}
				break;
			case 0xF6: {
				// Tune request
				WriteMessage(f, delta, "Tune request", data, 0);
			}
				break;
			case 0xF7: {
				// End of exclusive
				WriteMessage(f, delta, "End of exclusive", data, 0);
			}
				break;
			case 0xF8: {
				// Timing clock
				WriteMessage(f, delta, "Timing clock", data, 0);
			}
				break;
			case 0xFA: {
				// Start
				WriteMessage(f, delta, "Start", data, 0);
			}
				break;
			case 0xFB: {
				// Continue
				WriteMessage(f, delta, "Continue", data, 0);
			}
				break;
			case 0xFC: {
				// Stop
				WriteMessage(f, delta, "Stop", data, 0);
			}
				break;
			case 0xFE: {
				// Active sense
				WriteMessage(f, delta, "Active sense", data, 0);
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
					WriteMessage(f, delta, "Sequence number", &metaEventData, metaEventData.length());
					AddEvent(chan, delta, seq_name, metaEventData);
					WriteMessage(f, delta, "Sequence name", &metaEventData, metaEventData.length());
					break;
				case 0x01:
					// Text event
					AddEvent(chan, delta, text, metaEventData);
					WriteMessage(f, delta, "Text event", &metaEventData, metaEventData.length());
					break;
				case 0x02:
					// Copyright notice
					AddEvent(chan, delta, copy_not, metaEventData);
					WriteMessage(f, delta, "Copyright notice", &metaEventData, metaEventData.length());
					break;
				case 0x03:
					// Sequence/track name
					AddEvent(chan, delta, seq_name, metaEventData);
					WriteMessage(f, delta, "Sequence/track name", &metaEventData, metaEventData.length());
					break;
				case 0x04:
					// Instrument name
					AddEvent(chan, delta, inst_name, metaEventData);
					WriteMessage(f, delta, "Instrument name", &metaEventData, metaEventData.length());
					break;
				case 0x05:
					// Lyric
					AddEvent(chan, delta, text_lyric, metaEventData);
					WriteMessage(f, delta, "Lyric", &metaEventData, metaEventData.length());
					break;
				case 0x06:
					// Marker
					AddEvent(chan, delta, text_mark, metaEventData);
					WriteMessage(f, delta, "Marker", &metaEventData, metaEventData.length());
					break;
				case 0x07:
					// Cue point
					AddEvent(chan, delta, cue_point, metaEventData);
					WriteMessage(f, delta, "Cue point", &metaEventData, metaEventData.length());
					break;
				case 0x20:
					// MIDI channel prefix
					AddEvent(chan, delta, chan_prefix, metaEventData);
					WriteMessage(f, delta, "Midi channel prefix", &metaEventData, metaEventData.length());
					break;
				case 0x21:
					// Port message
					AddEvent(chan, delta, port_sel, metaEventData);
					WriteMessage(f, delta, "Midi port prefix", &metaEventData, metaEventData.length());
//					*data = data->right(data->length() - 2);
					break;
				case 0x2F:
					// End of track
					AddEvent(chan, delta, eot, metaEventData);
					WriteMessage(f, delta, "End of track", &metaEventData, metaEventData.length());
					break;
				case 0x51:
					// Set tempo
					AddEvent(chan, delta, set_tempo, metaEventData);
					WriteMessage(f, delta, "Set tempo", &metaEventData, metaEventData.length());
					break;
				case 0x54:
					// SMPTE offset
					AddEvent(chan, delta, smpte_offset, metaEventData);
					WriteMessage(f, delta, "SMPTE offset", &metaEventData, metaEventData.length());
					break;
				case 0x58:
					// Time signature
					AddEvent(chan, delta, time_sig, metaEventData);
					WriteMessage(f, delta, "Time signature", &metaEventData, metaEventData.length());
					break;
				case 0x59:
					// Key signature
					AddEvent(chan, delta, key_sig, metaEventData);
					WriteMessage(f, delta, "Key signature", &metaEventData, metaEventData.length());
					break;
				case 0x7F:
					// Sequencer specific meta-event
					AddEvent(chan, delta, seq_spec, metaEventData);
					WriteMessage(f, delta, "Sequencer specific event", &metaEventData, metaEventData.length());
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
			switch(command) {
			case 0: {
				// Note off
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, note_off, tmp);
				WriteMessage(f, delta, "Note off", &tmp, tmp.length());
			}
				break;
			case 1: {
				// Note on
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				if(tmp.at(1) != 0) {
					AddEvent(channel, delta, note_on, tmp);
					WriteMessage(f, delta, "Note on", &tmp, tmp.length());
				}
				else {
					AddEvent(channel, delta, note_off, tmp);
					WriteMessage(f, delta, "Note off", &tmp, tmp.length());
				}
			}
				break;
			case 2: {
				// Polyphonic key pressure (Aftertouch)
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, poly_key, tmp);
				WriteMessage(f, delta, "Polyphonic key pressure (Aftertouch)", &tmp, tmp.length());
			}
				break;
			case 3: {
				// Control change
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, cnt_change, tmp);
				WriteMessage(f, delta, "Control change", &tmp, tmp.length());
			}
				break;
			case 4: {
				// Program change
				QByteArray tmp = data->left(1);
				*data = data->right(data->length() - 1);
				AddEvent(channel, delta, pgm_change, tmp);
				WriteMessage(f, delta, "Program change", &tmp, tmp.length());
			}
				break;
			case 5: {
				// Channel pressure (Aftertouch)
				QByteArray tmp = data->left(1);
				*data = data->right(data->length() - 1);
				AddEvent(channel, delta, chan_press, tmp);
				WriteMessage(f, delta, "Channel pressure (Aftertouch)", &tmp, tmp.length());
			}
				break;
			case 6: {
				// Pitch wheel change
				QByteArray tmp = data->left(2);
				*data = data->right(data->length() - 2);
				AddEvent(channel, delta, pw_change, tmp);
				WriteMessage(f, delta, "Pitch wheel change", &tmp, tmp.length());
			}
				break;
			default:
				qDebug() << "Discarding " << QString::number(test, 16);
				break;
			}
		}
	}
}

