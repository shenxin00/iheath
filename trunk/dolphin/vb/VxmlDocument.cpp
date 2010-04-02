

#include "CVxmlModules.h"

VxmlDocument::VxmlDocument()
{
}


VxmlDocument::~VxmlDocument()
{
}
void VxmlDocument::Accept(VxmlAbsInterpreter *interpreter){
        interpreter->ExecComponte(this);
        ComponteList::iterator it;

	return;
}
int VxmlDocument::add(CBaseModule *child){
	_Child.push_back(child);
	return 0;
}
ComponteList VxmlDocument::getChild(){

	return _Child;
}

int VxmlDocument::GetEventList(VxmlEventList& pList){
	ComponteList::iterator it;
	for ( it=_Child.begin() ; it != _Child.end(); it++ ) {
		if((*it)->Type = TYPE_NOINPUT){
			VxmlEvent *pevent = new VxmlEvent;
			pevent->Type = TYPE_NOINPUT;
			pevent->Scope = this;
			pevent->context = (*it);
			pList.push_front(pevent);
		}
	}
	return 0;
}

int VxmlDocument::GetDialogMap(VxmlDialogMap& pMap){
	ComponteList::iterator it;
	//string = 
	for ( it=_Child.begin() ; it != _Child.end(); it++ ) {
		if((*it)->Type = TYPE_MENU){

			pMap.insert (pair<string,CBaseModule*>("menuid",this));  
		}else if((*it)->Type = TYPE_FORM){

			pMap.insert (pair<string,CBaseModule*>("formid",this));  
		}
	}
	return 0;
}

