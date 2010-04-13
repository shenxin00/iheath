#ifndef _CEVENTHANDLER_H_
#define _CEVENTHANDLER_H_

#include "VbCommon.h"
#include "CVxmlModules.h"



typedef stack<CBaseModule*> TActionStack;
typedef pair<string,TActions> TEventAction;
typedef map<string,TActions> TEventMapping;



/**
* @class CEventHandler
* @brief 
*
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class CEventHandler {

	/* member function */
	public:
		/**
		* @brief Constructor
		* @note 
		*/
		CEventHandler();
		/**
		* @brief virtual Destructor
		* @note 
		*/
		~CEventHandler();
		/**
		* @brief 
		* @note 
		* @param[in]
		* @param[in]
		* \exception 
		* \return error code
		*/
		void AddEventAction(string stEvent,CBaseModule* pAction);
		/**
		* @brief 
		* @note 
		* @param[in]
		* @param[in]
		* \exception 
		* \return error code
		*/
		void DelEventAction(string stEvent);
		
		/**
		* @brief 
		* @note 
		* @param[in]
		* @param[in]
		* \exception 
		* \return error code
		*/
		CBaseModule* pAction GetEventAction(string stEvent);
		

	/* member variables */
	private:
		//Execute content 
		TEventMapping		m_iEventMapping;	/**<		*/
};


#endif //  _CEVENTHANDLER_H_


