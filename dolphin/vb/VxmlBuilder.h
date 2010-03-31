#ifndef VxmlVxmlBUILDER_H
#define VxmlVxmlBUILDER_H

#include "comm.h"
#include "VxmlComponte.h"

using namespace std;




	/**
		@author sunyan <sunyan@optimedia.co.jp>
	*/
	class VxmlBuilder {
		public:
			VxmlBuilder();

			~VxmlBuilder();
			VxmlAbsComponte* BuildDocument(char* value);
			VxmlAbsComponte* BuildMenu(VxmlAbsComponte* parent, char* value);
			VxmlAbsComponte* BuildPrompt(VxmlAbsComponte* parent, char* value);
			VxmlAbsComponte* BuildChoice(VxmlAbsComponte* parent, char* value);
			VxmlAbsComponte* BuildObject(VxmlAbsComponte* parent, char* value);
			VxmlAbsComponte* BuildNoinput(VxmlAbsComponte* parent, char* value);

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


