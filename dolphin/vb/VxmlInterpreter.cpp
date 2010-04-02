

#include "VxmlInterpreter.h"

#include <iostream>
#include <string>

#include "CVxmlModules.h"

#include "VxmlPlatForm.h"




	VxmlInterpreter::VxmlInterpreter()
	{
	}


	VxmlInterpreter::~VxmlInterpreter()
	{
	}
	void VxmlInterpreter::ExecComponte ( VxmlDocument* doc )
	{
		cout << "VxmlDocument:" << endl;
		ComponteList children;
		ComponteList::iterator it;
		//VxmlEventList EventList;
		doc->GetEventList(_EventStack);
		
		doc->GetDialogMap(_DialogMap);


		children = doc->getChild();
			
		for ( it=children.begin() ; it != children.end(); it++ ) {
			//if((*it)->Type = TYPE_NOINPUT){
			//	continue;
			//}
			try{
				(*it)->Accept(this);
			}catch(string next){
				CBaseModule* nextDialog = NULL;
				nextDialog = CheckNext(next);
				if(nextDialog!=NULL){
					it = getNext(nextDialog,children);
					continue;
				}else{
					break;
				}
			}
		}

		return;
	}
	ComponteList::iterator VxmlInterpreter::getNext(CBaseModule* nextDialog,ComponteList children){
			ComponteList::iterator it;
			for ( it=children.begin() ; it != children.end(); it++ ) {
				if((*it)==nextDialog){
					return it;
				}
			}
			return it;
	}
	CBaseModule* VxmlInterpreter::CheckNext(string& next){
		VxmlDialogMap::iterator it;
		for ( it=_DialogMap.begin() ; it != _DialogMap.end(); it++ ) {
			if(next.compare((*it).first)){
				return  (*it).second;
			}			
		}
		return NULL;
	}

	void VxmlInterpreter::ExecComponte ( VxmlMenu* menu )
	{
		ComponteList children;
		PromptItemVector::iterator it;
		cout << "VxmlMenu:" << endl;

        PromptItemVector prompts = menu->collectPrompts();

        _PlatForm.QueuePrompts(prompts);
        
		children = menu->getChild();
		/*	
		for ( it=children.begin() ; it != children.end(); it++ ) {
			if((*it)->Type == TYPE_CHOICE){
				// get input
				cin >> _InputChoice; 
				//_InputChoice = 
			}
			(*it)->Accept(this);
		}
*/

		 // get input^M
                 cin >> _InputChoice;
                 //_InputChoice = ^M

		return;
	}
	void VxmlInterpreter::ExecComponte ( VxmlPrompt* prompt )
	{
		cout << "VxmlPrompt:" << endl;
		cout << prompt->getText() << endl;
		return;

	}
	void VxmlInterpreter::ExecComponte ( VxmlChoice* choice )
	{
		cout << "VxmlChoice:" << endl;
		string key =choice->getChoice();

		if(key.compare(_InputChoice) == 0){

			throw choice->getNext();
		}
	}
	void VxmlInterpreter::ExecComponte ( VxmlObject* ob )
	{
		cout << "VxmlObject:" << endl;
		return;
	}





