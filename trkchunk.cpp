#include "trkchunk.h"
#include "vlqscanner.h"
#include "globals.h"

TrkChunk::TrkChunk(QByteArray ba) {
    data = new QByteArray(ba.length(), 0);
    for(int index = 0; index < ba.length(); index++) {
        (*data)[index] = ba.at(index);
    }
    while(data->length() > 0) {
        u_int64_t delta = VLQScanner(*data).translated();
        int ptr = 0;
        uchar test = (uchar)(*data->mid(ptr, 1).data());
        ptr++;
        switch(test) {
        case 0xFF:
        {
            // This is a meta-event
            int tot_len = ptr;
            test = (uchar)(*data->mid(ptr, 1).data());
            ptr++;
            int len;
            QByteArray test2 = data->mid(ptr, 1);
            ptr++;
            len = uchar(*test2.data());
            QByteArray metaEventData = data->mid(ptr, len);
            ptr += len;
            tot_len = (ptr - tot_len) + 1;
            *data = data->right(data->length() - tot_len);
            switch(test) {
            case 0x00:
                // Sequence number
                events.append(new Event(delta, sequence_no, metaEventData));
                break;
            case 0x01:
                // Text event
                events.append(new Event(delta, text, metaEventData));
                break;
            case 0x02:
                // Copyright notice
                events.append(new Event(delta, copy_not, metaEventData));
                break;
            case 0x03:
                // Sequence/track name
                events.append(new Event(delta, seq_name, metaEventData));
                break;
            case 0x04:
                // Instrument name
                events.append(new Event(delta, inst_name, metaEventData));
                break;
            case 0x05:
                // Lyric
                events.append(new Event(delta, text_lyric, metaEventData));
                break;
            case 0x06:
                // Marker
                events.append(new Event(delta, text_mark, metaEventData));
                break;
            case 0x07:
                // Cue point
                events.append(new Event(delta, cue_point, metaEventData));
                break;
            case 0x20:
                // MIDI channel prefix
                events.append(new Event(delta, chan_prefix, metaEventData));
                break;
            case 0x2F:
                // End of track
                events.append(new Event(delta, eot, metaEventData));
                break;
            case 0x51:
                // Set tempo
                events.append(new Event(delta, set_tempo, metaEventData));
                break;
            case 0x54:
                // SMPTE offset
                events.append(new Event(delta, smpte_offset, metaEventData));
                break;
            case 0x58:
                // Time signature
                events.append(new Event(delta, time_sig, metaEventData));
                break;
            case 0x59:
                // Key signature
                events.append(new Event(delta, key_sig, metaEventData));
                break;
            case 0x7F:
                // Sequencer specific meta-event
                events.append(new Event(delta, seq_spec, metaEventData));
                break;
            default:
                break;
            }
        }
            break;
        default:
            if(test & 0x80) {
                // Look for channel voice or mode message
                if((test & 0xF0) == 0xF0) {
                    // Looks like a system common or system real-time message
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
                        events.append(new Event(delta, note_off, tmp));
                    }
                        break;
                    case 1: {
                        // Note on
                        QByteArray tmp = data->left(2);
                        *data = data->right(data->length() - 2);
                        events.append(new Event(delta, note_on, tmp));
                    }
                        break;
                    case 2: {
                        // Polyphonic key pressure (Aftertouch)
                        QByteArray tmp = data->left(2);
                        *data = data->right(data->length() - 2);
                        events.append(new Event(delta, poly_key, tmp));
                    }
                        break;
                    case 3: {
                        // Control change
                        QByteArray tmp = data->left(2);
                        *data = data->right(data->length() - 2);
                        events.append(new Event(delta, cnt_change, tmp));
                    }
                        break;
                    case 4: {
                        // Program change
                        QByteArray tmp = data->left(1);
                        *data = data->right(data->length() - 1);
                        events.append(new Event(delta, pgm_change, tmp));
                    }
                        break;
                    case 5: {
                        // Channel pressure (Aftertouch)
                        QByteArray tmp = data->left(1);
                        *data = data->right(data->length() - 1);
                        events.append(new Event(delta, chan_press, tmp));
                    }
                        break;
                    case 6: {
                        // Pitch wheel change
                        QByteArray tmp = data->left(2);
                        *data = data->right(data->length() - 2);
                        events.append(new Event(delta, pw_change, tmp));
                    }
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        }
    }
}

