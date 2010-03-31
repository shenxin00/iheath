#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

#include "VxmlParser.h"
#include "VxmlSAXHandler.h"


XERCES_CPP_NAMESPACE_USE



	VxmlParser::VxmlParser() {
		_Builder = new VxmlBuilder();
		_SAXHandler = new VxmlSAXHandler();
		
		_SAXHandler->setVxmlBuilder(_Builder);
	}
	VxmlParser::~VxmlParser() {
		delete _Builder;
		delete _SAXHandler;	
	}

	VxmlDocument* VxmlParser::DoParser(string& file) {

		/// @todo implement me
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
		//DefaultHandler* defaultHandler = new VxmlSAXHandler();
		DefaultHandler* defaultHandler = _SAXHandler;
		
		parser->setContentHandler(defaultHandler);
		parser->setErrorHandler(defaultHandler);

		try {
			parser->parse(file.c_str());
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

		//delete defaultHandler;
		
		return NULL;
	}

