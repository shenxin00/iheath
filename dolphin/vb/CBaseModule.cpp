#include "CBaseModule.h"

	CBaseModule::CBaseModule() {
	}


	CBaseModule::~CBaseModule() {
	}
	void CBaseModule::Accept(VxmlAbsInterpreter* interpreter) {
		return;
	}
	int CBaseModule::add(CBaseModule* child) {
		_Child.push_back(child);
		return 0;
	}
	ComponteList CBaseModule::getChild() {
		return _Child;    
	}

