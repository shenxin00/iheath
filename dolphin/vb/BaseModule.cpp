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
CBaseModule::CBaseModule() {

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
CBaseModule::~CBaseModule() {

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
void CBaseModule::Accept(VxmlAbsInterpreter* interpreter) {
	return;
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
int CBaseModule::add(CBaseModule* child) {
	_Child.push_back(child);
	return 0;
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
ComponteList CBaseModule::getChild() {
	return _Child;    
}

