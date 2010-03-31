#ifndef VxmlVxmlPARSER_H
#define VxmlVxmlPARSER_H


#include "comm.h"
#include "VxmlComponte.h"
#include "VxmlBuilder.h"
#include "VxmlSAXHandler.h"

/**
	@author sunyan <sunyan@optimedia.co.jp>
*/
class VxmlParser {
	public:
		VxmlParser();
		~VxmlParser();
		VxmlDocument* DoParser(string& file);
	private:
		VxmlBuilder	*		_Builder;
		VxmlSAXHandler*	_SAXHandler;
};


#endif


