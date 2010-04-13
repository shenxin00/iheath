

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
	// init document root to NULL 
	m_iVxmlDoc			= NULL;
	m_iCurrentModule	= NULL;
	
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
		m_iVxmlTagIDMap.insert(TVxmlTagID(VxmlTagArray[i].stTagName,VxmlTagArray[i].eTagID));
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
int CVxmlBuilder::GetTagID(string& tagName)
{

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
void CVxmlBuilder::ToUpperCase(string& str)
{
	
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
void CVxmlBuilder::ToLowerCase(string& str)
{
	
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
int CVxmlBuilder::StartModule(char* pTagName,TTagAttributes& iAttributes);
{
	CBaseModule		pModule = NULL;
	EModuleType		eType;
	TTagAttribute	iAttr;
	string			stAttrName;
	string			stAttrType;
	string			stAttrValue;


	// get TagID by TagName
	string stTagName= string(name);
	EVxmlTagID eTagID = GetTagID(stTagName);
	
	// build a new Module 
	pModule = new CBaseModule();
	// on error retunr 
	if(pModule == NULL)
	{
		return ERR_RTN;
	}
		
	// set Module TagID	
	switch (eTagID)
	{
		case TAG_ID_ASSIGN:
			eType = TYPE_ASSIGN;
			break;
		case TAG_ID_AUDIO:
			eType = TYPE_AUDIO;
			break;
		case TAG_ID_BLOCK:
			eType = TYPE_BLOCK;
			break;
		case TAG_ID_CATCH:
			eType = TYPE_CATCH;
			break;
		case TAG_ID_CHOICE:
			eType = TYPE_CHOICE;
			break;
		case TAG_ID_CLEAR:
			eType = TYPE_CLEAR;
			break;
		case TAG_ID_DISCONNECT:
			eType = TYPE_DISCONNECT;
			break;
		case TAG_ID_ELSE:
			eType = TYPE_ELSE;
			break;
		case TAG_ID_ELSEIF:
			eType = TYPE_ELSEIF;
			break;
		case TAG_ID_ENUMERATE:
			eType = TYPE_ENUMERATE;
			break;
		case TAG_ID_ERROR:
			//eType = TYPE_ERROR;

			// act as Cactch with attribute event=error
			eType = TYPE_CATCH;
			stAttrName = string("event");
			//stAttrType = string(iAttr.pType);
			stAttrValue = string("error");
			
			pModule->SetAttribute(stAttrName,stAttrValue);
			
			break;
		case TAG_ID_EXIT:
			eType = TYPE_EXIT;
			break;
		case TAG_ID_FIELD:
			eType = TYPE_FIELD;
			break;
		case TAG_ID_FILLED:
			eType = TYPE_FILLED;
			break;
		case TAG_ID_FORM:
			eType = TYPE_FORM;
			break;
		case TAG_ID_GOTO:
			eType = TYPE_GOTO;
			break;
		case TAG_ID_GRAMMAR:
			eType = TYPE_GRAMMAR;
			break;
		case TAG_ID_HELP:
			//eType = TYPE_HELP;

			// act as Cactch with attribute event=error
			eType = TYPE_CATCH;
			stAttrName = string("event");
			//stAttrType = string(iAttr.pType);
			stAttrValue = string("help");
			
			pModule->SetAttribute(stAttrName,stAttrValue);

			break;
		case TAG_ID_IF:
			eType = TYPE_IF;
			break;
		case TAG_ID_INITIAL:
			eType = TYPE_INITIAL;
			break;
		case TAG_ID_LINK:
			eType = TYPE_LINK;
			break;
		case TAG_ID_LOG:
			eType = TYPE_LOG;
			break;
		case TAG_ID_MENU:
			eType = TYPE_MENU;
			break;
		case TAG_ID_META:
			eType = TYPE_META;
			break;
		case TAG_ID_METADATA:
			eType = TYPE_METADATA;
			break;
		case TAG_ID_NOINPUT:
			//eType = TYPE_NOINPUT;

			// act as Cactch with attribute event=error
			eType = TYPE_CATCH;
			stAttrName = string("event");
			//stAttrType = string(iAttr.pType);
			stAttrValue = string("noinput");
			
			pModule->SetAttribute(stAttrName,stAttrValue);

			break;
		case TAG_ID_NOMATCH:
			//eType = TYPE_NOMATCH;

			// act as Cactch with attribute event=error
			eType = TYPE_CATCH;
			stAttrName = string("event");
			//stAttrType = string(iAttr.pType);
			stAttrValue = string("nomatch");
			
			pModule->SetAttribute(stAttrName,stAttrValue);

			break;
		case TAG_ID_OBJECT:
			eType = TYPE_OBJECT;
			break;
		case TAG_ID_OPTION:
			eType = TYPE_OPTION;
			break;
		case TAG_ID_PARAM:
			eType = TYPE_PARAM;
			break;
		case TAG_ID_PROMPT:
			eType = TYPE_PROMPT;
			break;
		case TAG_ID_PROPERTY:
			eType = TYPE_PROPERTY;
			break;
		case TAG_ID_RECORD:
			eType = TYPE_RECORD;
			break;
		case TAG_ID_REPROMPT:
			eType = TYPE_REPROMPT;
			break;
		case TAG_ID_RETURN:
			eType = TYPE_RETURN;
			break;
		case TAG_ID_SCRIPT:
			eType = TYPE_SCRIPT;
			break;
		case TAG_ID_SUBDIALOG:
			eType = TYPE_SUBDIALOG;
			break;
		case TAG_ID_SUBMIT:
			eType = TYPE_SUBMIT;
			break;
		case TAG_ID_THROW:
			eType = TYPE_THROW;
			break;
		case TAG_ID_TRANSFER:
			eType = TYPE_TRANSFER;
			break;
		case TAG_ID_VALUE:
			eType = TYPE_VALUE;
			break;
		case TAG_ID_VAR:
			eType = TYPE_VAR;
			break;
		case TAG_ID_VXML:
			eType = TYPE_VXML;
			break;
		default:
	}
	pModule->m_eType = eType;
	
	// Set Attributes to the new module
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
	
	// add the module to the current module as child
	m_iCurrentModule->SetChild(pModule);
	pModule->m_iParent = m_iCurrentModule;

	// and set the modules as the current module 
	m_iCurrentModule = pModule;

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
int CVxmlBuilder::EndModule(char* pTagName)
{
	m_iCurrentModule = m_iCurrentModule->m_iParent;
	
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
int CVxmlBuilder::BuildText(char* pValue,int nLength)
{
	// build a new Module 
	pModule = new CBaseModule();
	// on error return 
	if(pModule == NULL)
	{
		return ERR_RTN;
	}
	
	//set Text Element's content 
	pModule->m_eType	= TYPE_TEXT;
	pModule->m_stText	= string(pValue);
	
	// add the module to the current module as child 
	m_iCurrentModule->SetChild(pModule);
	pModule->m_iParent = m_iCurrentModule;
	
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
int CVxmlBuilder::BuildDocument(char* pValue)
{
	//on m_iVxmlDoc is not null return error
	if(m_iVxmlDoc == NULL){
		m_iVxmlDoc = new CDocumentModule();
	}else{
		return ERR_RTN;
	}
	
	// on error return 
	if(pModule == NULL)
	{
		return ERR_RTN;
	}
	
	m_iVxmlDoc->m_iParent	= NULL;
	m_iVxmlDoc->m_stURI		= string(pValue);
	m_iVxmlDoc->m_eType		= TYPE_VXML;

	m_iCurrentModule		= (CBaseModule*)m_iVxmlDoc;
	
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
CDocumentModule* CVxmlBuilder::GetProduct() {
	return m_iVxmlDoc;
}

/**
* @brief 
* @note 
* @param[in ]
* \exception 
* \return void
*/
void CVxmlBuilder::SetErrorCode(int code)
{
	m_nErrorCode = code;
}
/**
* @brief 
* @note 
* @param[in ]
* \exception 
* \return void
*/
int CVxmlBuilder::GetErrorCode(void)
{
	return m_nErrorCode;
}


