

#include "CVxmlModules.h"



	CPromptModule::CPromptModule()
	{
	}


	CPromptModule::~CPromptModule()
	{
	}

	void CPromptModule::Accept ( VxmlAbsInterpreter *interpreter )
	{
		interpreter->ExecComponte ( this );
	}
	int CPromptModule::add ( CBaseModule *child )
	{
		_Child.push_back ( child );
		return 0;
	}
	ComponteList CPromptModule::getChild()
	{

		return _Child;
	}
	string CPromptModule::getText()
	{
		return "This is a Prompt!";
	}

