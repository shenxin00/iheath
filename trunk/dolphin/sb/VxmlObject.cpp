

#include "VxmlComponte.h"



    VxmlObject::VxmlObject() {
    }


    VxmlObject::~VxmlObject() {
    }


    int VxmlObject::add(VxmlAbsComponte* child) {
        _Child.push_back(child);
        return 0;;
    }

    ComponteList VxmlObject::getChild() {
        return VxmlAbsComponte::getChild();
    }

    void VxmlObject::Accept(VxmlAbsInterpreter* interpreter) {
                interpreter->ExecComponte(this);
        ComponteList::iterator it;
        for ( it=_Child.begin() ; it != _Child.end(); it++ ) {
            (*it)->Accept(interpreter);
        }
	return;
    }


