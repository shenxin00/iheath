#ifndef _VXMLSAXHANDLER_H_
#define _VXMLSAXHANDLER_H_

#include <xercesc/sax2/DefaultHandler.hpp>
XERCES_CPP_NAMESPACE_USE;


#include "CVxmlBuilder.h"

class VxmlSAXHandler : public DefaultHandler {
	public:
		
		void startDocument();
		
		void startElement(
			const XMLCh* const uri,
			const XMLCh* const localname,
			const XMLCh* const qname,
			const Attributes& attrs
		);
		
		void characters(
			const XMLCh* const chars,
			const unsigned int length
		);
		
		void endElement(
			const XMLCh* const uri,
			const XMLCh* const localname,
			const XMLCh* const qname
		);

		void fatalError(const SAXParseException& exc);
		void error(const SAXParseException& exc);

		void SetBuilder(CVxmlBuilder* Builder);

	private:
		/* data */
		CVxmlBuilder*		m_iBuilder;
		
};

#endif //_VXMLSAXHANDLER_H_
