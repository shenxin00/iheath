
#include "VxmlPlatForm.h"


        VxmlPlatForm::VxmlPlatForm(){
        }

        VxmlPlatForm::~VxmlPlatForm(){
        }

        int VxmlPlatForm::QueuePrompts(PromptItemVector prompts){
            PromptItemVector::iterator it;
            for(it = prompts.begin(); it != prompts.end(); it++){
                cout << "type=" << (*it)._Type;
                cout << "\n value" << (*it)._Value;            
            }
                    
        }
/*
        int VxmlPlatForm::callObject(VxmlAbsComponte *child){

        
        }
        int VxmlPlatForm::setProptety(string name,string value){

        
        }
*/



