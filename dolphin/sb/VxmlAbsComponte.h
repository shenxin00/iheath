#ifndef VxmlVxmlABSCOMPONTE_H
#define VxmlVxmlABSCOMPONTE_H


#include <list>
#include <map>
#include <string>
#include <iostream>


#include "VxmlAbsInterpreter.h"

using namespace std;


#define ComponteList list<VxmlAbsComponte*>

#define TYPE_DOCUMENT	0
#define TYPE_MENU			1
#define TYPE_FORM			2
#define TYPE_PROMPT		3
#define TYPE_CHOICE		4
#define TYPE_OBJECT		5

#define TYPE_NOINPUT		91
#define TYPE_NOMCTCH		92
#define TYPE_ERROR		93
#define TYPE_CATCH			94








	

	/**
	* @author sunyan <sunyan@optimedia.co.jp>
	*/
	class VxmlAbsComponte {
public:
		int Type;
		int Index;

		VxmlAbsComponte();

		~VxmlAbsComponte();

		virtual void Accept(VxmlAbsInterpreter *interpreter);
		virtual int add(VxmlAbsComponte *child);
		virtual ComponteList getChild();
//protected:
//		DOMNode* _Node;
		string			_Value;
		ComponteList	_Child;
	};


#define VxmlDialogMap map<string,VxmlAbsComponte*>

#endif


