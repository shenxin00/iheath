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
		/**
		* @brief Constructor
		* @note 
		*/
		CBaseModule();
		/**
		* @brief virtual Destructor
		* @note release all children modules ( by delete the pointer )
		*/
		virtual ~CBaseModule();
		
		/**
		* @brief add a sub module to current module.
		* @note 
		* @param[in] child the sub module to add. 
		* \exception 
		* \return error code
		*/
		int SetChild(CBaseModule *pChild);

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
		* @param[in] position  
		* @param[out] sub module's pointer
		* @param[out] sub module's  type
		* \exception 
		* \return error code
		*/
		int GetChild(int nIndex, CBaseModule** ppChild, EModuleType* eType);

		/**
		* @brief add a attribute to current module.
		* @note 
		* @param[in] attribute Name
		* @param[in] attribute Value
		* \exception 
		* \return error code
		*/
		int SetAttribute(string& stName, string& stValue);
		
		/**
		* @brief get a attribute's value by attributes name.
		* @note 
		* @param[in] attribute Name
		* @param[out] ttribute Value
		* \exception 
		* \return error code
		*/
		int GetAttribute(string& stName, string& stValue);
		

		virtual void Accept(VxmlAbsInterpreter *interpreter);

	/* member variables */
	public:
		EModuleType		m_eType;		/**< Module's Type				*/
	private:
//		string			m_stValue;		/**< */
		TAttributes		m_iAttributes;	/**< string based attributes	*/
		TModules		m_iChildren;	/**< Sub Module's list 			*/
};


#endif //_BASE_MODULES_H_


