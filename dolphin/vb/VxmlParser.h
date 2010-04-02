#ifndef VxmlVxmlPARSER_H
#define VxmlVxmlPARSER_H


#include "comm.h"
#include "CVxmlModules.h"
#include "VxmlBuilder.h"
#include "VxmlSAXHandler.h"

/**
	@author sunyan <sunyan@hit.edu.cn>
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


