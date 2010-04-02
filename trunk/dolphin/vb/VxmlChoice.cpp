

#include "CVxmlModules.h"


VxmlChoice::VxmlChoice() {
	_Next = "next";
	_Choice = "choice";
}


VxmlChoice::~VxmlChoice() {
}


void VxmlChoice::Accept(VxmlAbsInterpreter *interpreter){
	interpreter->ExecComponte(this);
	return;
}
int VxmlChoice::add(CBaseModule *child){
	return 0;
}
ComponteList VxmlChoice::getChild(){

	return _Child;
}

string VxmlChoice::getChoice(){

	return _Choice;
}
string VxmlChoice::getNext(){

	return _Next;
}

