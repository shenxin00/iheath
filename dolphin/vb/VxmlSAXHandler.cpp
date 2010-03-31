
#include "comm.h"
#include "VxmlSAXHandler.h"
#include <xercesc/sax2/Attributes.hpp>


void VxmlSAXHandler::startDocument(){
	_Builder->BuildDocument("document_name");
}


void VxmlSAXHandler::startElement(
	const XMLCh* const uri,
	const XMLCh* const localname,
	const XMLCh* const qname,
	const Attributes& attrs
){
	//handler Tag
	char* tagName = XMLString::transcode(localname);
	_Builder->BuildElement(tagName);
	XMLString::release(&tagName);
	
	//handler tag's Attributes
//	cout<<"attrs:"<<endl;
	for(int i=0;i<attrs.getLength();i++){
		char* attr_name = XMLString::transcode(attrs.getLocalName(i));
		char* attr_type = XMLString::transcode(attrs.getType(i));
		char* attr_value = XMLString::transcode(attrs.getValue(i));
		
//		cout<<"\tLocalName="<<XMLString::transcode(attrs.getLocalName(i));
//		cout<<"\tType="<<XMLString::transcode(attrs.getType(i));
//		cout<<"\tVaule="<<XMLString::transcode(attrs.getValue(i))<<endl;
		
		_Builder->BuildAttribute(attr_name,attr_value);
		
		XMLString::release(&attr_name);
		XMLString::release(&attr_type);
		XMLString::release(&attr_value);
	}

	
	return;
}
void VxmlSAXHandler::fatalError(const SAXParseException& exc){
#if 0
	cout<<__FUNCTION__<<endl;
#endif
	char* message = XMLString::transcode(exc.getMessage());
	cout << "Fatal Error: " << message
		<< " at line: " << exc.getLineNumber()
		<< endl;

	return;
}

void VxmlSAXHandler::endElement(
	const XMLCh* const uri,
	const XMLCh* const localname,
	const XMLCh* const qname
){
#if 0
	cout<<__FUNCTION__<<endl;
	cout<<"uri="<<uri<<endl;
	cout<<"localname="<<localname<<endl;
	cout<<"qname="<<qname<<endl;
#endif
	return;
}



void VxmlSAXHandler::characters(
	const XMLCh* const chars,
	const unsigned int length
){
#if 0
	cout<<__FUNCTION__<<endl;
	cout<<"chars="<<chars<<endl;
	cout<<"length="<<length<<endl;
#endif
	return;
}
void VxmlSAXHandler::error(const SAXParseException& exc){
//	cout<<__FUNCTION__<<endl;
#if 0
	char* message = XMLString::transcode(exc.getMessage());
	cout << " Error: " << message
		<< " at line: " << exc.getLineNumber()
		<< endl;
	return;
#endif

}

#if 0
#endif

void VxmlSAXHandler::setVxmlBuilder(VxmlBuilder* Builder){
	_Builder = Builder;
}
