#ifndef VxmlVxmlBUILDER_H
#define VxmlVxmlBUILDER_H

#include "VbCommon.h"
#include "CVxmlModules.h"

using namespace std;




	/**
		@author sunyan <sunyan@hit.edu.cn>
	*/
	class VxmlBuilder {
		public:
			VxmlBuilder();

			~VxmlBuilder();
			CBaseModule* BuildDocument(char* value);
			CBaseModule* BuildMenu(CBaseModule* parent, char* value);
			CBaseModule* BuildPrompt(CBaseModule* parent, char* value);
			CBaseModule* BuildChoice(CBaseModule* parent, char* value);
			CBaseModule* BuildNoinput(CBaseModule* parent, char* value);

			CDocumentModule* getProduct();
		
			//interface
			int BuildElement(char* tagName);
			int BuildAttribute(char* attrName,char* value);
			
		private:
			int getTagID(string& tagName);
			CDocumentModule* _VxmlDoc;
			VxmlTagIDMap  _VxmlTagIDMap;
	};


#endif


