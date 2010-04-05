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
		virtual ~CBaseModule();
		
		/**
		* @brief add a sub module to current module.
		* @note 
		* @param[in] child the sub module to add. 
		* \exception 
		* \return error code
		*/
		int SetChild(CBaseModule *child);

		/**
		* @brief calculate the sub modules counts
		* @note 
		* \exception 
		* \return sub modules counts
		*/
		int GetChildCount(void);

		/**
		* @brief get the sub module's pointer and type by position index 
		* @note 
		* @param[in] position index 
		* @param[out] sub module's pointer
		* @param[out] sub module's  type
		* \exception 
		* \return error code
		*/
		int GetChild(int index, CBaseModule** child, TModuleType* type);

		/**
		* @brief add a attribute to current module.
		* @note 
		* @param[in] attribute name
		* @param[in] attribute value
		* \exception 
		* \return error code
		*/
		int SetAttribute(string& name, string& value);
		
		/**
		* @brief get a attribute's value by attributes name.
		* @note 
		* @param[in] attribute name
		* @param[out] ttribute value
		* \exception 
		* \return error code
		*/
		int GetAttribute(string& name, string& value);

		

		virtual void Accept(VxmlAbsInterpreter *interpreter);

//	protected:
//		DOMNode* _Node;
	/* member variables */
	public:
		EModuleType		m_eType;		/**< Module's Type				*/
	private:
//		string			m_strValue;		/**< */
		TAttributes		m_iAttributes;	/**< string based attributes	*/
		TModules		m_iChildren;	/**< Sub Module's list 			*/
};


#endif //_BASE_MODULES_H_


