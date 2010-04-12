#include "CBaseModule.h"



/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CBaseModule::CBaseModule()
{
	m_iParent = NULL;
	
}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
CBaseModule::~CBaseModule()
{
	CBaseModule* child = NULL;
	/* release all child moudles */
	for( int index=0; index < m_iChildren.size(); index++ ){
		/* get the child's pointer */
		child = m_iChildren.at(index);
		/* make sure the child's pointer is not zero */
		assert( child );
		/* release the child */
		delete child;
	}

}


/**
* @brief add a sub module to current module.
* @note 
* @param[in] child the sub module to add. 
* \exception 
* \return error code
*/
int CBaseModule::SetChild(CBaseModule *pChild)
{
	m_iChildren.push_back(pChild);
	
	return OK_RTN;
}

/**
* @brief calculate the sub modules counts
* @note 
* \exception 
* \return sub modules counts
*/
int CBaseModule::GetChildCount(void)
{
	return m_iChildren.size();
}

/**
* @brief get the sub module's pointer and type by position index 
* @note 
* @param[in] position index 
* @param[out] sub module's pointer
* @param[out] sub module's  type
* \exception 
* \return error code
*/
int CBaseModule::GetChild(int nIndex, CBaseModule** ppChild, EModuleType* eType)
{
	*ppChild = m_iChildren.at(nIndex);
	*eType = child->m_eType;
	return OK_RTN;
}

/**
* @brief add a attribute to current module.
* @note 
* @param[in] attribute name
* @param[in] attribute value
* \exception 
* \return error code
*/
int CBaseModule::SetAttribute(string& stName, string& stValue)
{
	m_iAttributes.insert(TAttribute(stName,stValue));
}

/**
* @brief get a attribute's value by attributes name.
* @note 
* @param[in] attribute name
* @param[out] ttribute value
* \exception 
* \return error code
*/
int CBaseModule::GetAttribute(string& stName, string& stValue)
{

	TAttributes::iterator iter = stringCounts.find(stName);

	if( iter == stringCounts.end() )
	{
//cout << "You typed '" << iter->first << "' " << iter->second << " time(s)" << endl;
		return ERR_RTN;
	}
	
	stValue = iter->second;
	return OK_RTN;
}


/**
* @brief 
* @note 
* 
* @param[out] 
* @param[in] 
* @param[in] 
* \exception 
* \return 
*/
void CBaseModule::Accept(VxmlAbsInterpreter* interpreter)
{
	return;
}

