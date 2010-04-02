

#include "CVxmlModules.h"



    CMenuModule::CMenuModule()
: CBaseModule() {
    }


    CMenuModule::~CMenuModule() {
    }
    void CMenuModule::Accept(VxmlAbsInterpreter *interpreter) {
        interpreter->ExecComponte(this);
        return;
    }
    int CMenuModule::add(CBaseModule *child) {
        _Child.push_back(child);
        return 0;
    }
    ComponteList CMenuModule::getChild() {

        return _Child;
    }


    PromptItemVector CMenuModule::collectPrompts(){
        PromptItemVector prompts;
        ComponteList::iterator it;
        for ( it=_Child.begin() ; it != _Child.end(); it++ ) {
            if((*it)->Type == TYPE_PROMPT){
                PromptItem* item = new PromptItem();
                item->_Type = TYPE_PROMPT;
        //        item->_Value = (*it)->getText();
                
                prompts.push_back(*item);
            
            }
        }
        return prompts;    	

    }


