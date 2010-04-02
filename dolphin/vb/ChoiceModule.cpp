

#include "CVxmlModules.h"


CChoiceModule::CChoiceModule() {
	_Next = "next";
	_Choice = "choice";
}


CChoiceModule::~CChoiceModule() {
}


void CChoiceModule::Accept(VxmlAbsInterpreter *interpreter){
	interpreter->ExecComponte(this);
	return;
}
int CChoiceModule::add(CBaseModule *child){
	return 0;
}
ComponteList CChoiceModule::getChild(){

	return _Child;
}

string CChoiceModule::getChoice(){

	return _Choice;
}
string CChoiceModule::getNext(){

	return _Next;
}

