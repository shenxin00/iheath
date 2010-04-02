

#include "CVxmlModules.h"



    VxmlMenu::VxmlMenu()
: CBaseModule() {
    }


    VxmlMenu::~VxmlMenu() {
    }
    void VxmlMenu::Accept(VxmlAbsInterpreter *interpreter) {
        interpreter->ExecComponte(this);
        return;
    }
    int VxmlMenu::add(CBaseModule *child) {
        _Child.push_back(child);
        return 0;
    }
    ComponteList VxmlMenu::getChild() {

        return _Child;
    }


    PromptItemVector VxmlMenu::collectPrompts(){
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


