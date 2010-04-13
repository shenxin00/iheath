#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

#include "CVxmlParser.h"
#include "CVxmlSAXHandler.h"


XERCES_CPP_NAMESPACE_USE


/**
* @brief Constructor
* @note 
*/
CVxmlParser::CVxmlParser()
{
	m_iBuilder = new CVxmlBuilder();
	m_iSAXHandler = new CVxmlSAXHandler();
	
	m_iSAXHandler->SetBuilder(m_iBuilder);
}
/**
* @brief virtual Destructor
* @note 
*/
CVxmlParser::~CVxmlParser()
{
	delete m_iBuilder;
	delete m_iSAXHandler;
}
/**
* @brief 
* @note 
* @param[in]
* @param[in]
* \exception 
* \return error code
*/

CDocumentModule* CVxmlParser::DoParser(string& stFileUri)
{
	int nErrorCode;
	
	//init xerces 
	try {
		 XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n";
		cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return NULL;
	}

	//const char* xmlFile = ;	//  cast to [char*]
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

	//DefaultHandler* defaultHandler = new DefaultHandler();
	DefaultHandler* defaultHandler = m_iSAXHandler;
	
	parser->setContentHandler(defaultHandler);
	parser->setErrorHandler(defaultHandler);

	try {
		parser->parse(stFileUri.c_str());
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return NULL;
	}
	catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return NULL;
	}
	catch (...) {
		cout << "Unexpected Exception \n" ;
		return NULL;
	}

	delete parser;
	
	
	/*	error check */
	nErrorCode = m_iBuilder->GetErrorCode();
	if(nErrorCode){
		return NULL;
	}
	
	return m_iBuilder->GetProduct();
}

