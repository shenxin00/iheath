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
			virtual void ExecComponte ( CDocumentModule* doc );
			virtual void ExecComponte ( CMenuModule* doc );
			virtual void ExecComponte ( CPromptModule* doc );
			virtual void ExecComponte ( CChoiceModule* doc );
	private:
		CEventList _EventStack;
		VxmlDialogMap _DialogMap;
		string		 _InputChoice;
        VxmlPlatForm  _PlatForm;
    
		CBaseModule* CheckNext(string& next);
		TModules::iterator getNext(CBaseModule* nextDialog,TModules children);

	};



#endif


