#ifndef _BASE_MODULES_H_
#define _BASE_MODULES_H_


/**
* Header files
*/
#include "VbCommon.h"
#include "VxmlAbsInterpreter.h"


/**
* @class CBaseModule
* @brief 
*
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class CBaseModule
{
	/* member functions */
	public:
		CBaseModule();
		~CBaseModule();
		virtual void Accept(VxmlAbsInterpreter *interpreter);
		virtual int add(CBaseModule *child);
		virtual ComponteList getChild();

	protected:
//		DOMNode* _Node;
	/* member variables */
	public:
		TModuleType enType;			/**< Module's Type */
		int 		Index;			/**< ??				*/

	private:
		string			m_strValue;		/**< */
		ComponteList	m_iChildren;	/**< */
	};


#define VxmlDialogMap map<string,CBaseModule*>

#endif //_BASE_MODULES_H_


