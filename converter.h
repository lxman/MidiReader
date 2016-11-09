#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include "globals.h"

class Converter {
	public:
		Converter();
		QString EventTypeToString(EventType et);
		QString NoteToString(uchar note);
		QString ControllerToString(uchar id);
		QString ProgramChangeToString(uchar id);
};

#endif // CONVERTER_H
