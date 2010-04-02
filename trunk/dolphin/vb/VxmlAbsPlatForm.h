#ifndef VxmlVxmlABSPLATFORM_H
#define VxmlVxmlABSPLATFORM_H


#include <list>
#include <map>
#include <string>
#include <iostream>

#include "comm.h"

using namespace std;




	

    /**
    	@author sunyan <sunyan@hit.edu.cn>
    */
    class VxmlAbsPlatForm {
public:

        VxmlAbsPlatForm();

        ~VxmlAbsPlatForm();

        virtual int QueuePrompts(PromptItemVector prompts);
/*
        virtual int callObject(CBaseModule *child);
        virtual int setProptety(string name,string value);
 */
   };





#endif

