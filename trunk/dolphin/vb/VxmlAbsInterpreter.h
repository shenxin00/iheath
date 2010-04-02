#ifndef VxmlVxmlABSINTERPRETER_H
#define VxmlVxmlABSINTERPRETER_H




	class CDocumentModule;
	class CMenuModule;
	class CPromptModule;
	class CChoiceModule;
	/**
		@author sunyan <sunyan@hit.edu.cn>
	*/
	class VxmlAbsInterpreter
	{
		public:
			virtual void ExecComponte ( CDocumentModule* doc ) =0;
			virtual void ExecComponte ( CMenuModule* doc ) =0;
			virtual void ExecComponte ( CPromptModule* doc ) =0;
			virtual void ExecComponte ( CChoiceModule* doc ) =0;
	};

#endif


