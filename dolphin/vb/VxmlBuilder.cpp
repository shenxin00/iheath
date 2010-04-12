

#include "VxmlBuilder.h"
#include "VxmlModules.h"


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CVxmlBuilder::CVxmlBuilder() {
	/* init document root to NULL */
	__VxmlDoc = NULL;
	/* */
	TVxmlTag VxmlTagArray[TAG_NUM] = {
		{TAG_ID_ASSIGN,		"ASSIGN"	},
		{TAG_ID_AUDIO,		"AUDIO"		},
		{TAG_ID_BLOCK,		"BLOCK"		},
		{TAG_ID_CATCH,		"CATCH"		},
		{TAG_ID_CHOICE,		"CHOICE"	},
		{TAG_ID_CLEAR,		"CLEAR"		},
		{TAG_ID_DISCONNECT,	"DISCONNECT"},
		{TAG_ID_ELSE,		"ELSE"		},
		{TAG_ID_ELSEIF,		"ELSEIF"	},
		{TAG_ID_ENUMERATE,	"ENUMERATE"	},
		{TAG_ID_ERROR,		"ERROR"		},
		{TAG_ID_EXIT,		"EXIT"		},
		{TAG_ID_FIELD,		"FIELD"		},
		{TAG_ID_FILLED,		"FILLED"	},
		{TAG_ID_FORM,		"FORM"		},
		{TAG_ID_GOTO,		"GOTO"		},
		{TAG_ID_GRAMMAR,	"GRAMMAR"	},
		{TAG_ID_HELP,		"HELP"		},
		{TAG_ID_IF,			"IF"		},
		{TAG_ID_INITIAL,	"INITIAL"	},
		{TAG_ID_LINK,		"LINK"		},
		{TAG_ID_LOG,		"LOG"		},
		{TAG_ID_MENU,		"MENU"		},
		{TAG_ID_META,		"META"		},
		{TAG_ID_METADATA,	"METADATA"	},
		{TAG_ID_NOINPUT,	"NOINPUT"	},
		{TAG_ID_NOMATCH,	"NOMATCH"	},
		{TAG_ID_OBJECT,		"OBJECT"	},
		{TAG_ID_OPTION,		"OPTION"	},
		{TAG_ID_PARAM,		"PARAM"		},
		{TAG_ID_PROMPT,		"PROMPT"	},
		{TAG_ID_PROPERTY,	"PROPERTY"	},
		{TAG_ID_RECORD,		"RECORD"	},
		{TAG_ID_REPROMPT,	"REPROMPT"	},
		{TAG_ID_RETURN,		"RETURN"	},
		{TAG_ID_SCRIPT,		"SCRIPT"	},
		{TAG_ID_SUBDIALOG,	"SUBDIALOG"	},
		{TAG_ID_SUBMIT,		"SUBMIT"	},
		{TAG_ID_THROW,		"THROW"		},
		{TAG_ID_TRANSFER,	"TRANSFER"	},
		{TAG_ID_VALUE,		"VALUE"		},
		{TAG_ID_VAR,		"VAR"		},
		{TAG_ID_VXML,		"VXML"		},
	};
	int i;
	
	/* init Vxml tags map */
	for(i= 0;i<TAG_NUM;i++){
		__VxmlTagIDMap.insert(pair<string,int>(VxmlTagArray[i].TagName,VxmlTagArray[i].TagID));
	}
	
	/* */
	
}
/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CVxmlBuilder::~CVxmlBuilder() {
	
}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
int CVxmlBuilder::GetTagID(string& tagName){
	
	/* change tagname to uppercase */
	ToUpperCase(tagName);
	
	/* find the TagID by tagname */
	VxmlTagIDMap::iterator iter = _VxmlTagIDMap.find(tagName);
	if( iter != _VxmlTagIDMap.end() ) {
// cout << "TAG_NAME=" << iter->first << "\tTAG_ID=" << iter->second << endl;
		/* return the tagID */
		return iter->second;
	}
	/* on error retunr error code */
	return ERR_RTN;
}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
void CVxmlBuilder::ToUpperCase(string& str){
	
	int i;
	for(i= 0;i<str.length();i++){
		tagName.at(i) = toupper(str.at(i));
	}
	return;
}

/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
void CVxmlBuilder::ToLowerCase(string& str){
	
	int i;
	for(i= 0;i<str.length();i++){
		tagName.at(i) = tolower(str.at(i));
	}
	return;
}

/**
* @brief Build a module by tag name and attributes
* @note 
* @param[in] TagName
* @param[in] Attributes
* \exception 
* \return error code
*/
int BuildElement(char* pTagName,TTagAttributes& iAttributes);
{	
	CBaseModule		pModule = NULL;
	TTagAttribute	iAttr;
	string			stAttrName;
	string			stAttrType;
	string			stAttrValue;
	

	/* get TagID by TagName 		*/
	string stTagName= string(name);
	EVxmlTagID eTagID = GetTagID(stTagName);
	
	/* Budild a Module by TagID		*/
	switch (eTagID)
	{
		case TAG_ID_ASSIGN:
			break;
		case TAG_ID_AUDIO:
			break;
		case TAG_ID_BLOCK:
			break;
		case TAG_ID_CATCH:
			break;
		case TAG_ID_CHOICE:
			break;
		case TAG_ID_CLEAR:
			break;
		case TAG_ID_DISCONNECT:
			break;
		case TAG_ID_ELSE:
			break;
		case TAG_ID_ELSEIF:
			break;
		case TAG_ID_ENUMERATE:
			break;
		case TAG_ID_ERROR:
			break;
		case TAG_ID_EXIT:
			break;
		case TAG_ID_FIELD:
			break;
		case TAG_ID_FILLED:
			break;
		case TAG_ID_FORM:
			break;
		case TAG_ID_GOTO:
			break;
		case TAG_ID_GRAMMAR:
			break;
		case TAG_ID_HELP:
			break;
		case TAG_ID_IF:
			break;
		case TAG_ID_INITIAL:
			break;
		case TAG_ID_LINK:
			break;
		case TAG_ID_LOG:
			break;
		case TAG_ID_MENU:
			break;
		case TAG_ID_META:
			break;
		case TAG_ID_METADATA:
			break;
		case TAG_ID_NOINPUT:
			break;
		case TAG_ID_NOMATCH:
			break;
		case TAG_ID_OBJECT:
			break;
		case TAG_ID_OPTION:
			break;
		case TAG_ID_PARAM:
			break;
		case TAG_ID_PROMPT:
			break;
		case TAG_ID_PROPERTY:
			break;
		case TAG_ID_RECORD:
			break;
		case TAG_ID_REPROMPT:
			break;
		case TAG_ID_RETURN:
			break;
		case TAG_ID_SCRIPT:
			break;
		case TAG_ID_SUBDIALOG:
			break;
		case TAG_ID_SUBMIT:
			break;
		case TAG_ID_THROW:
			break;
		case TAG_ID_TRANSFER:
			break;
		case TAG_ID_VALUE:
			break;
		case TAG_ID_VAR:
			break;
		case TAG_ID_VXML:
			break;
	}
	
	
	/* */
	if(pModule == NULL)
	{
		return ERR_RTN;
	}
	
	/* Set Attributes to the new module	*/
	for( int i = 0; i < iAttributes.size(); i++)
	{		
		iAttr = iAttributes.at(i);
		
		stAttrName = string(iAttr.pName);
		stAttrType = string(iAttr.pType);
		stAttrValue = string(iAttr.pValue);
		
		// change Attributes to LowerCase 
		ToLowerCase(stAttrName);
		
		pModule->SetAttribute(stAttrName,stAttrValue);
		
	}
	
	return OK_RTN;

}



/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
int CBaseModule* CVxmlBuilder::BuildDocument(char* value) {


	if(m_iVxmlDoc == NULL){
		m_iVxmlDoc = new CDocumentModule();
		m_iVxmlDoc->_Value = value;
		m_iVxmlDoc->Type = TYPE_DOCUMENT;
	}else{
cout <<__FUNCTION__<<"_VxmlDoc is not null"<<endl;
		return ERR_RTN;
	}
	
	return OK_RTN ;
}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
int CBaseModule* CVxmlBuilder::BuildMenu(CBaseModule* parent, char* value) {
	CMenuModule* componte = new CMenuModule();
	componte->_Value = value;
	parent->add(componte);
	componte->Type = TYPE_MENU;
	return componte;

}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CBaseModule* CVxmlBuilder::BuildPrompt(CBaseModule* parent, char* value) {
	CPromptModule* componte = new CPromptModule();
	componte->_Value = value;
	parent->add(componte);
	componte->Type = TYPE_PROMPT;
	return componte;
}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CBaseModule* CVxmlBuilder::BuildChoice(CBaseModule* :parent, char* value) {
	CChoiceModule* componte = new CChoiceModule();
	componte->_Value = value;
	parent->add(componte);
	componte->Type = TYPE_CHOICE;
	return componte;
}


#if 0
/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/

CBaseModule* CVxmlBuilder::BuildNoinput(CBaseModule* parent, char* value) {
	VxmlNoinput* componte = new VxmlNoinput();
	componte->_Value = node;
	parent->add(componte);
	componte->Type = TYPE_NOINPUT;
	return componte;
}
#endif

/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CDocumentModule* CVxmlBuilder::getProduct() {
	return _VxmlDoc;
}
