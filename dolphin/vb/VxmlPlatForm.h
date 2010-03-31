#ifndef VxmlVxmlPLATFORM_H
#define VxmlVxmlPLATFORM_H


#include "VxmlAbsPlatForm.h"


using namespace std;


/*
	typedef PromptItem struct _PromptItem {
		int _Type;
		string _Value;
	}

#define	PromptItemVector list<PromptItem>
	
	
*/
    /**
    	@author sunyan <sunyan@optimedia.co.jp>
    */
    class VxmlPlatForm {
public:

        VxmlPlatForm();

        ~VxmlPlatForm();

        virtual int QueuePrompts(PromptItemVector prompts);
/*
        virtual int callObject(VxmlAbsComponte *child);
        virtual int setProptety(string name,string value);
*/
//protected:
    };






#endif

