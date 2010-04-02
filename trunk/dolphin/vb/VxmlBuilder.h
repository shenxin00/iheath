#ifndef VxmlVxmlBUILDER_H
#define VxmlVxmlBUILDER_H

#include "comm.h"
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
			CBaseModule* BuildObject(CBaseModule* parent, char* value);
			CBaseModule* BuildNoinput(CBaseModule* parent, char* value);

			VxmlDocument* getProduct();
		
			//interface
			int BuildElement(char* tagName);
			int BuildAttribute(char* attrName,char* value);
			
		private:
			int getTagID(string& tagName);
			VxmlDocument* _VxmlDoc;
			VxmlTagIDMap  _VxmlTagIDMap;
	};


#endif


