#include "converter.h"
#include <QStringList>

Converter::Converter() {

}

QString Converter::EventTypeToString(EventType et) {
	switch (et) {
	case sequence_no:
		return "Sequence number";
		break;
	case text:
		return "Text";
		break;
	case copy_not:
		return "Copyright notice";
		break;
	case inst_name:
		return "Instrument name";
		break;
	case text_lyric:
		return "Lyric";
		break;
	case text_mark:
		return "Text mark";
		break;
	case cue_point:
		return "Cue point";
		break;
	case chan_prefix:
		return "Channel prefix";
		break;
	case eot:
		return "End of track";
		break;
	case set_tempo:
		return "Set tempo";
		break;
	case smpte_offset:
		return "SMPTE offset";
		break;
	case time_sig:
		return "Time signature";
		break;
	case key_sig:
		return "Key signature";
		break;
	case seq_spec:
		return "Sequencer specific";
		break;
	case seq_name:
		return "Sequencer name";
		break;
	case note_off:
		return "Note off";
		break;
	case note_on:
		return "Note on";
		break;
	case poly_key:
		return "Polyphonic key pressure";
		break;
	case cnt_change:
		return "Control change";
		break;
	case pgm_change:
		return "Program change";
		break;
	case chan_press:
		return "Channel pressure";
		break;
	case pw_change:
		return "Pitch wheel change";
		break;
	case sys_ex:
		return "System exclusive";
		break;
	case song_ptr:
		return "Song pointer";
		break;
	case song_sel:
		return "Song select";
		break;
	case tune_req:
		return "Tune request";
		break;
	case eoe:
		return "End of exclusive";
		break;
	case tim_clk:
		return "Time click";
		break;
	case start:
		return "Start";
		break;
	case cont:
		return "Continue";
		break;
	case stop:
		return "Stop";
		break;
	case act_sens:
		return "Active sense";
		break;
	case rst:
		return "Reset";
		break;
	case port_sel:
		return "Port select";
		break;
	default:
		break;
	}
	return "";
}

QString Converter::NoteToString(uchar note) {
	QStringList noteVals = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
	return noteVals[note];
}

QString Converter::ControllerToString(uchar id) {
	QStringList ControllerVals1 = { "Bank Select", "Modulation Wheel", "Breath controller", "Undefined", "Foot Pedal",
									"Portamento Time", "Data Entry", "Volume", "Balance", "Undefined", "Pan position",
									"Expression", "Effect Control 1", "Effect Control 2", "Undefined", "Undefined",
									"Ribbon Controller or General Purpose Slider 1", "Knob 1 or General Purpose Slider 2",
									"General Purpose Slider 3", "Knob 2 General Purpose Slider 4", "Knob 3 or Undefined",
									"Knob 4 or Undefined", "Undefined", "Undefined", "Undefined", "Undefined", "Undefined",
									"Undefined", "Undefined", "Undefined", "Undefined", "Undefined" };
	QStringList ControllerVals2 = { "Hold Pedal (on/off)", "Portamento (on/off)", "Sustenuto Pedal (on/off)", "Soft Pedal (on/off)",
									"Legato Pedal (on/off)", "Hold 2 Pedal (on/off)", "Sound Variation", "Resonance (aka Timbre)",
									"Sound Release Time", "Sound Attack Time", "Frequency Cutoff", "Sound Control 6", "Sound Control 7",
									"Sound Control 8", "Sound Control 9", "Sound Control 10", "Decay or General Purpose Button 1",
									"Hi Pass Filter Frequency or General Purpose Button 2", "General Purpose Button 3",
									"General Purpose Button 4", "Portamento", "Undefined", "Undefined", "Undefined", "Undefined",
									"Undefined", "Undefined", "Reverb Level", "Tremolo Level", "Chorus Level",
									"Celeste Level or Detune", "Phaser Level", "Data Button increment", "Data Button decrement",
									"Non-registered Parameter (LSB)", "Non-registered Parameter (MSB)", "Registered Parameter (LSB)",
									"Registered Parameter (MSB)", "Undefined", "Undefined", "Undefined", "Undefined",
									"Undefined", "Undefined", "Undefined", "Undefined", "Undefined", "Undefined",
									"Undefined", "Undefined", "Undefined", "Undefined", "Undefined", "Undefined",
									"Undefined", "Undefined", "All Sound Off", "All Controllers Off", "Local Keyboard (on/off)",
									"All Notes Off", "Omni Mode Off", "Omni Mode On", "Mono Operation", "Poly Operation",
									"Poly mode on"};
	if(id < 32) return ControllerVals1[id] + " (MSB)";
	if(id < 64) return ControllerVals1[id - 32] + " (LSB)";
	return ControllerVals2[id - 64];
}

QString Converter::ProgramChangeToString(uchar id) {
	QStringList ProgramVals = { "Acoustic Grand", "Bright Acoustic", "Electric Grand", "Honky-Tonk", "Electric Piano 1", "Electric Piano 2",
								"Harpsichord", "Clavinet", "elesta", "Glockenspiel", "Music Box", "Vibraphone",
								"Marimba", "Xylophone", "Tubular Bells", "Dulcimer", "Drawbar Organ", "Percussive Organ",
								"Rock Organ", "Church Organ", "Reed Organ", "Accordion", "Harmonica", "Tango Accordian",
								"Acoustic Guitar(nylon)", "Acoustic Guitar(steel)", "Electric Guitar(jazz)", "Electric Guitar(clean)", "Electric Guitar(muted)", "Overdriven Guitar",
								"Distortion Guitar", "Guitar Harmonics", "Acoustic Bass", "Electric Bass (finger)", "Electric Bass (pick)", "Fretless Bass",
								"Slap Bass 1", "Slap Bass 2", "Synth Bass 1", "Synth Bass 2", "Violin", "Viola",
								"Cello", "Contrabass", "Tremolo Strings", "Pizzicato Strings", "Orchestral Strings", "Timpani",
								"String Ensemble 1", "String Ensemble 2", "SynthStrings 1", "SynthStrings 2", "Choir Aahs", "Voice Oohs",
								"Synth Voice", "Orchestra Hit", "Trumpet", "Trombone", "Tuba", "Muted Trumpet",
								"French Horn", "Brass Section", "SynthBrass 1", "SynthBrass 2", "Soprano Sax", "Alto Sax",
								"Tenor Sax", "Baritone Sax", "Oboe", "English Horn", "Bassoon", "Clarinet",
								"Piccolo", "Flute", "Recorder", "Pan Flute", "Blown Bottle", "Skakuhachi",
								"Whistle", "Ocarina", "Lead 1 (square)", "Lead 2 (sawtooth)", "Lead 3 (calliope)", "Lead 4 (chiff)",
								"Lead 5 (charang)", "Lead 6 (voice)", "Lead 7 (fifths)", "Lead 8 (bass+lead)", "Pad 1 (new age)", "Pad 2 (warm)",
								"Pad 3 (polysynth)", "Pad 4 (choir)", "Pad 5 (bowed)", "Pad 6 (metallic)", "Pad 7 (halo)", "Pad 8 (sweep)",
								"FX 1 (rain)", "FX 2 (soundtrack)", "FX 3 (crystal)", "FX 4 (atmosphere)", "FX 5 (brightness)", "FX 6 (goblins)",
								"FX 7 (echoes)", "FX 8 (sci-fi)", "Sitar", "Banjo", "Shamisen", "Koto",
								"Kalimba", "Bagpipe", "Fiddle", "Shanai", "Tinkle Bell", "Agogo",
								"Steel Drums", "Woodblock", "Taiko Drum", "Melodic Tom", "Synth Drum", "Reverse Cymbal",
								"Guitar Fret Noise", "Breath Noise", "Seashore", "Bird Tweet", "Telephone Ring", "Helicopter",
								"Applause", "Gunshot" };
	return ProgramVals[id];
}
