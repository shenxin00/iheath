

#include "CVxmlInterpreter.h"

#include <iostream>
#include <string>

#include "CVxmlModules.h"
/**
* @brief Constructor
* @note 
*/
CVxmlInterpreter::CVxmlInterpreter()
{
	
}

/**
* @brief Destructor
* @note
*/
CVxmlInterpreter::~CVxmlInterpreter()
{
	
}

/**
* @brief 
* @note 
* @param[in]
* \exception 
* \return error code
*/
void CVxmlInterpreter::Execute(CDocumentModule* pDoc)
{
	int				nChildrenCount;
	CBaseModule		pModule;
	string			stEvent;
	
	if(pDoc == NULL){
		return;
	}
	
	nChildrenCount = pDoc->GetChildCount()
	// pre function
	for(int nPos= 0;nPos < nChildrenCount;nPos++
	{
		pModule = pDoc->GetChild(nIndex);
		//treat <catch> 
		if(pModule->m_eType == TYPE_CATCH)
		{
			if(pModule->GetAttribute(sting("event"),stEvent) == OK_RTN)
			{
				m_iEventHandler.AddEventAction(stEvent,pModule);
			}
			
		}
	}

		
	//main function
	
}
/**
* @brief 
* @note 
* @param[in]
* \exception 
* \return error code
*/
void CVxmlInterpreter::Execute(CDocumentModule* pDoc, string& stDialog)
{
	
}
/**
* @brief 
* @note 
* @param[in]
* \exception 
* \return error code
*/
void CVxmlInterpreter::Execute(string& stDialog)
{
	
}
/**
* @brief 
* @note 
* @param[in]
* \exception 
* \return error code
*/
void CVxmlInterpreter::ExecuteModule( CBaseModule* pModule)
{

}


#include "VxmlPlatForm.h"





	void CVxmlInterpreter::ExecComponte ( CDocumentModule* doc )
	{
		cout << "CDocumentModule:" << endl;
		TModules children;
		TModules::iterator it;
		//CEventList EventList;
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
	TModules::iterator CVxmlInterpreter::getNext(CBaseModule* nextDialog,TModules children){
			TModules::iterator it;
			for ( it=children.begin() ; it != children.end(); it++ ) {
				if((*it)==nextDialog){
					return it;
				}
			}
			return it;
	}
	CBaseModule* CVxmlInterpreter::CheckNext(string& next){
		VxmlDialogMap::iterator it;
		for ( it=_DialogMap.begin() ; it != _DialogMap.end(); it++ ) {
			if(next.compare((*it).first)){
				return  (*it).second;
			}			
		}
		return NULL;
	}

	void CVxmlInterpreter::ExecComponte ( CMenuModule* menu )
	{
		TModules children;
		PromptItemVector::iterator it;
		cout << "CMenuModule:" << endl;

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
	void CVxmlInterpreter::ExecComponte ( CPromptModule* prompt )
	{
		cout << "CPromptModule:" << endl;
		cout << prompt->getText() << endl;
		return;

	}
	void CVxmlInterpreter::ExecComponte ( CChoiceModule* choice )
	{
		cout << "CChoiceModule:" << endl;
		string key =choice->getChoice();

		if(key.compare(_InputChoice) == 0){

			throw choice->getNext();
		}
	}





