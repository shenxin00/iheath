

#include <cctype>
#include <algorithm>
#include "VxmlBuilder.h"
#include "CVxmlModules.h"


VxmlTag VxmlTagArray[TAG_NUM] = {
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

	VxmlBuilder::VxmlBuilder() {
		_VxmlDoc = NULL;
		int i;
		//init #define VxmlTagIDMap map<string,int>

		
		for(i= 0;i<TAG_NUM;i++){
			//_VxmlTagIDMap.insert( make_pair( "Key the Three", 66667 ) );
			_VxmlTagIDMap.insert(pair<string,int>(VxmlTagArray[i].TagName,VxmlTagArray[i].TagID));
		}
	}

	VxmlBuilder::~VxmlBuilder() {
		
	}
	int VxmlBuilder::getTagID(string& tagName){


	int i;
	for(i= 0;i<tagName.length();i++){
		tagName.at(i) = toupper(tagName.at(i));
//		tagName.at(i) = tolower(tagName.at(i));
	}
	
		
		VxmlTagIDMap::iterator iter = _VxmlTagIDMap.find(tagName);
		if( iter != _VxmlTagIDMap.end() ) {
cout << "TAG_NAME=" << iter->first << "\tTAG_ID=" << iter->second << endl;
			return iter->second;
		}
		return -1;
	}




	int VxmlBuilder::BuildElement(char* name){
		string tagName= string(name);
		int tagID = getTagID(tagName);
		switch (tagID){
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
	
	}

	int VxmlBuilder::BuildAttribute(char* name,char* value){
		string attrName= string(name);
		string attrValue= string(value);
cout << "\t" << attrName << " = " << attrValue<< endl;
	
	}

	CBaseModule* VxmlBuilder::BuildDocument(char* value) {
		if(_VxmlDoc == NULL){
			_VxmlDoc = new CDocumentModule();
			_VxmlDoc->_Value = value;
			_VxmlDoc->Type = TYPE_DOCUMENT;
		}else{
			cout <<__FUNCTION__<<"_VxmlDoc is not null"<<endl;
		}
		
		return _VxmlDoc ;
	}
	
	
	CBaseModule* VxmlBuilder::BuildMenu(CBaseModule* parent, char* value) {
		CMenuModule* componte = new CMenuModule();
		componte->_Value = value;
		parent->add(componte);
		componte->Type = TYPE_MENU;
		return componte;

	}
	CBaseModule* VxmlBuilder::BuildPrompt(CBaseModule* parent, char* value) {
		CPromptModule* componte = new CPromptModule();
		componte->_Value = value;
		parent->add(componte);
		componte->Type = TYPE_PROMPT;
		return componte;
	}
	CBaseModule* VxmlBuilder::BuildChoice(CBaseModule* :parent, char* value) {
		CChoiceModule* componte = new CChoiceModule();
		componte->_Value = value;
		parent->add(componte);
		componte->Type = TYPE_CHOICE;
		return componte;
	}
/*
	CBaseModule* VxmlBuilder::BuildNoinput(CBaseModule* parent, char* value) {
		VxmlNoinput* componte = new VxmlNoinput();
		componte->_Value = node;
		parent->add(componte);
		componte->Type = TYPE_NOINPUT;
		return componte;
	}
*/
	CDocumentModule* VxmlBuilder::getProduct() {
		return _VxmlDoc;
	}

