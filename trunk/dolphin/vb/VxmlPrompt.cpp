

#include "CVxmlModules.h"



	VxmlPrompt::VxmlPrompt()
	{
	}


	VxmlPrompt::~VxmlPrompt()
	{
	}

	void VxmlPrompt::Accept ( VxmlAbsInterpreter *interpreter )
	{
		interpreter->ExecComponte ( this );
	}
	int VxmlPrompt::add ( CBaseModule *child )
	{
		_Child.push_back ( child );
		return 0;
	}
	ComponteList VxmlPrompt::getChild()
	{

		return _Child;
	}
	string VxmlPrompt::getText()
	{
		return "This is a Prompt!";
	}

