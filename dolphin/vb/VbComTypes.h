#ifndef _COM_TYPES_H_
#define _COM_TYPES_H_

typedef struct ST_PROMPT_ITEM {
	int _Type;
	string _Value;
}PromptItem;

typedef struct ST_VXML_TAG{
	int		TagID;
	string	TagName;
}VxmlTag;

typedef list<PromptItem> PromptItemVector
typedef map<string,int> VxmlTagIDMap


#endif //_COM_TYPES_H_



