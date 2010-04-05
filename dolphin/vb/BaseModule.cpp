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

}


/**
* @brief add a sub module to current module.
* @note 
* @param[in] child the sub module to add. 
* \exception 
* \return error code
*/
int CBaseModule::SetChild(CBaseModule *child)
{
	m_iChildren.push_back(child);
	
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
int CBaseModule::GetChild(int index, CBaseModule** child, TModuleType* type)
{
	*child = m_iChildren.at(index);
	*type = child->m_eType;
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
int CBaseModule::SetAttribute(string& name, string& value)
{
	m_iAttributes.insert (pair<string,string>(name,value));
}

/**
* @brief get a attribute's value by attributes name.
* @note 
* @param[in] attribute name
* @param[out] ttribute value
* \exception 
* \return error code
*/
int CBaseModule::GetAttribute(string& name, string& value)
{

	TAttributes::iterator iter = stringCounts.find(name);

	if( iter == stringCounts.end() )
	{
//cout << "You typed '" << iter->first << "' " << iter->second << " time(s)" << endl;
		return ERR_RTN;
	}
	
	value = iter->second;
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

