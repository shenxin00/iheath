#ifndef VxmlVxmlABSPLATFORM_H
#define VxmlVxmlABSPLATFORM_H


#include <list>
#include <map>
#include <string>
#include <iostream>

#include "comm.h"

using namespace std;




	

    /**
    	@author sunyan <sunyan@optimedia.co.jp>
    */
    class VxmlAbsPlatForm {
public:

        VxmlAbsPlatForm();

        ~VxmlAbsPlatForm();

        virtual int QueuePrompts(PromptItemVector prompts);
/*
        virtual int callObject(VxmlAbsComponte *child);
        virtual int setProptety(string name,string value);
 */
   };





#endif

