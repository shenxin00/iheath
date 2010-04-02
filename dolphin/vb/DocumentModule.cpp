

#include "CVxmlModules.h"

CDocumentModule::CDocumentModule()
{
}


CDocumentModule::~CDocumentModule()
{
}
void CDocumentModule::Accept(VxmlAbsInterpreter *interpreter){
        interpreter->ExecComponte(this);
        ComponteList::iterator it;

	return;
}
int CDocumentModule::add(CBaseModule *child){
	_Child.push_back(child);
	return 0;
}
ComponteList CDocumentModule::getChild(){

	return _Child;
}

int CDocumentModule::GetEventList(CEventList& pList){
	ComponteList::iterator it;
	for ( it=_Child.begin() ; it != _Child.end(); it++ ) {
		if((*it)->Type = TYPE_NOINPUT){
			CEvent *pevent = new CEvent;
			pevent->Type = TYPE_NOINPUT;
			pevent->Scope = this;
			pevent->context = (*it);
			pList.push_front(pevent);
		}
	}
	return 0;
}

int CDocumentModule::GetDialogMap(VxmlDialogMap& pMap){
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

