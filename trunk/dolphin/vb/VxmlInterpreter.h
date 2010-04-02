#ifndef VxmlVxmlINTERPRETER_H
#define VxmlVxmlINTERPRETER_H

#include "VxmlAbsInterpreter.h"
#include "CVxmlModules.h"

#include "VxmlPlatForm.h"


	/**
		@author sunyan <sunyan@hit.edu.cn>
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
    
		CBaseModule* CheckNext(string& next);
		ComponteList::iterator getNext(CBaseModule* nextDialog,ComponteList children);

	};



#endif


