#ifndef VxmlVxmlABSINTERPRETER_H
#define VxmlVxmlABSINTERPRETER_H




	class VxmlDocument;
	class VxmlMenu;
	class VxmlPrompt;
	class VxmlChoice;
	class VxmlObject;
	/**
		@author sunyan <sunyan@hit.edu.cn>
	*/
	class VxmlAbsInterpreter
	{
		public:
			virtual void ExecComponte ( VxmlDocument* doc ) =0;
			virtual void ExecComponte ( VxmlMenu* doc ) =0;
			virtual void ExecComponte ( VxmlPrompt* doc ) =0;
			virtual void ExecComponte ( VxmlChoice* doc ) =0;
			virtual void ExecComponte ( VxmlObject* doc ) =0;
	};

#endif


