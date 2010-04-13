
#include "VbCommon.h"
#include "CVxmlSAXHandler.h"
#include <xercesc/sax2/Attributes.hpp>


void CVxmlSAXHandler::startDocument(){
	_Builder->BuildDocument("document_name");
}


void CVxmlSAXHandler::startElement(
	const XMLCh* const uri,
	const XMLCh* const localname,
	const XMLCh* const qname,
	const Attributes& attrs
){
	TTagAttributes iAttributes
	char* pTagName;	
	TTagAttribute iAttr;
		
	//get Tag's name and Attributes
	pTagName = XMLString::transcode(localname);
//	cout<<"attrs:"<<endl;
	for(int i=0;i<attrs.getLength();i++)
	{
		//get the Attribute's infomation
		iAttr.pName			= XMLString::transcode(attrs.getLocalName(i));
		iAttr.pType			= XMLString::transcode(attrs.getType(i));
		iAttr.pValue		= XMLString::transcode(attrs.getValue(i));
	
		// add to attributes's vector in order to send to Vxml Builder
		iAttributes.push_back(iAttr);
		
//		cout<<"\tLocalName="<<XMLString::transcode(attrs.getLocalName(i));
//		cout<<"\tType="<<XMLString::transcode(attrs.getType(i));
//		cout<<"\tVaule="<<XMLString::transcode(attrs.getValue(i))<<endl;
	}
	
	// build the Module by pass the infomation to Vxml Builder
	m_iBuilder->StartModule(pTagName,iAttributes);
	
	// release the resource 
	XMLString::release(&pTagName);
	for(int i=0;i<iAttributes.size();i++)
	{
		iAttr = iAttributes.at(i);
		XMLString::release(&iAttr.pName);
		XMLString::release(&iAttr.pAttrType);
		XMLString::release(&iAttr.pAttrValue);
	}
	
	return;
}
void CVxmlSAXHandler::fatalError(const SAXParseException& exc){
#if 0
	cout<<__FUNCTION__<<endl;
#endif
	char* message = XMLString::transcode(exc.getMessage());
	cout << "Fatal Error: " << message
		<< " at line: " << exc.getLineNumber()
		<< endl;

	return;
}

void CVxmlSAXHandler::endElement(
	const XMLCh* const uri,
	const XMLCh* const localname,
	const XMLCh* const qname
){
	char* pTagName;

	pTagName = XMLString::transcode(localname);
	m_iBuilder->EndModule(pTagName);
	XMLString::release(&pTagName);

#if 0
	cout<<__FUNCTION__<<endl;
	cout<<"uri="<<uri<<endl;
	cout<<"localname="<<localname<<endl;
	cout<<"qname="<<qname<<endl;
#endif
	return;
}



void CVxmlSAXHandler::characters(
	const XMLCh* const chars,
	const unsigned int length
){
	char* pValue;	
	pValue = XMLString::transcode(chars);
	m_iBuilder->BuildText(pValue,chars);
	XMLString::release(&pValue);
#if 0
	cout<<__FUNCTION__<<endl;
	cout<<"chars="<<chars<<endl;
	cout<<"length="<<length<<endl;
#endif
	return;
}
void CVxmlSAXHandler::error(const SAXParseException& exc){
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

void CVxmlSAXHandler::SetBuilder(CVxmlBuilder* Builder){
	m_iBuilder = Builder;
}
