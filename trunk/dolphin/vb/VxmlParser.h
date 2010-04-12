#ifndef VxmlVxmlPARSER_H
#define VxmlVxmlPARSER_H


#include "VbCommon.h"
#include "CVxmlModules.h"
#include "CVxmlBuilder.h"
#include "VxmlSAXHandler.h"

/**
	@author sunyan <sunyan@hit.edu.cn>
*/
class VxmlParser {
	public:
		VxmlParser();
		~VxmlParser();
		CDocumentModule* DoParser(string& file);
	private:
		CVxmlBuilder	*		_Builder;
		VxmlSAXHandler*	_SAXHandler;
};


#endif


