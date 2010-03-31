#ifndef Vxml_VxmlCOMPONTE_H
#define Vxml_VxmlCOMPONTE_H
#include "VxmlAbsComponte.h"
#include "comm.h"





struct VxmlEvent
{
	int Type;
	VxmlAbsComponte *Scope;
	VxmlAbsComponte *context;
};

#define VxmlEventList list<struct VxmlEvent*>



/**
	@author sunyan <sunyan@optimedia.co.jp>
*/
class VxmlDocument: public VxmlAbsComponte{
public:
    VxmlDocument();

    virtual ~VxmlDocument();

	virtual void Accept(VxmlAbsInterpreter *interpreter);
	virtual int add(VxmlAbsComponte *child);
	virtual ComponteList getChild();
	
	int GetEventList(VxmlEventList& pList);

	int GetDialogMap(VxmlDialogMap& pMap);
};


/**
	@author sunyan <sunyan@optimedia.co.jp>
*/
class VxmlMenu : public VxmlAbsComponte
{
public:
    VxmlMenu();

    ~VxmlMenu();
	virtual void Accept(VxmlAbsInterpreter *interpreter);
	virtual int add(VxmlAbsComponte *child);
	virtual ComponteList getChild();

    PromptItemVector collectPrompts();

};

/**
	@author sunyan <sunyan@optimedia.co.jp>
*/
class VxmlPrompt: public VxmlAbsComponte{
public:
    VxmlPrompt();
	
    ~VxmlPrompt();
	virtual void Accept(VxmlAbsInterpreter *interpreter);
	virtual int add(VxmlAbsComponte *child);
	virtual ComponteList getChild();
	string getText();
private: 
	string Text;
};



/**
	@author sunyan <sunyan@optimedia.co.jp>
*/
class VxmlObject : public VxmlAbsComponte
{
public:
    VxmlObject();

    ~VxmlObject();

    virtual int add(VxmlAbsComponte* child);
    virtual ComponteList getChild();
    virtual void Accept(VxmlAbsInterpreter* interpreter);

};

    /**
    	@author sunyan <sunyan@optimedia.co.jp>
    */
class VxmlChoice : public VxmlAbsComponte {
public:
        VxmlChoice();

        ~VxmlChoice();
        virtual void Accept(VxmlAbsInterpreter *interpreter);
        virtual int add(VxmlAbsComponte *child);
        virtual ComponteList getChild();
		
		
		string getChoice();
		string getNext();
private:
		string _Choice;
		string _Next;

    };



#endif 
