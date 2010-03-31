#ifndef VxmlVxmlINTERPRETER_H
#define VxmlVxmlINTERPRETER_H

#include "VxmlAbsInterpreter.h"
#include "VxmlComponte.h"

#include "VxmlPlatForm.h"


	/**
		@author sunyan <sunyan@optimedia.co.jp>
	*/
	class VxmlInterpreter:public VxmlAbsInterpreter
	{
		public:
			VxmlInterpreter();

			~VxmlInterpreter();
			virtual void ExecComponte ( VxmlDocument* doc );
			virtual void ExecComponte ( VxmlMenu* doc );
			virtual void ExecComponte ( VxmlPrompt* doc );
			virtual void ExecComponte ( VxmlChoice* doc );
			virtual void ExecComponte ( VxmlObject* doc );
	private:
		VxmlEventList _EventStack;
		VxmlDialogMap _DialogMap;
		string		 _InputChoice;
        VxmlPlatForm  _PlatForm;
    
		VxmlAbsComponte* CheckNext(string& next);
		ComponteList::iterator getNext(VxmlAbsComponte* nextDialog,ComponteList children);

	};



#endif


