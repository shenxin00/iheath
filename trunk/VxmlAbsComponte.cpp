#include "VxmlAbsComponte.h"

	VxmlAbsComponte::VxmlAbsComponte() {
	}


	VxmlAbsComponte::~VxmlAbsComponte() {
	}
	void VxmlAbsComponte::Accept(VxmlAbsInterpreter* interpreter) {
		return;
	}
	int VxmlAbsComponte::add(VxmlAbsComponte* child) {
		_Child.push_back(child);
		return 0;
	}
	ComponteList VxmlAbsComponte::getChild() {
		return _Child;    
	}

