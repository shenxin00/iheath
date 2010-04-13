#ifndef VxmlVxmlINTERPRETER_H
#define VxmlVxmlINTERPRETER_H

#include "VxmlAbsInterpreter.h"
#include "CVxmlModules.h"

#include "VxmlPlatForm.h"


/**
	@author sunyan <sunyan@hit.edu.cn>
*/
class VxmlInterpreter
{
	/* member functions */
	public:
		/**
		* @brief Constructor
		* @note 
		*/
		VxmlInterpreter();
		/**
		* @brief Destructor
		* @note
		*/
		~VxmlInterpreter();
		/**
		* @brief 
		* @note 
		* @param[in]
		* \exception 
		* \return error code
		*/
		void Execute(CDocumentModule* pDoc);
		/**
		* @brief 
		* @note 
		* @param[in]
		* \exception 
		* \return error code
		*/
		void Execute(CDocumentModule* pDoc, string& stDialog);
		/**
		* @brief 
		* @note 
		* @param[in]
		* \exception 
		* \return error code
		*/
		void Execute(string& stDialog);
		/**
		* @brief 
		* @note 
		* @param[in]
		* \exception 
		* \return error code
		*/
		void ExecuteModule( CBaseModule* pModule);

	private:

	/* member variables */
	private:
		//Execute content 
		TEventActions		m_iEventActions;	/**<		*/
		/**
		!Todo
			input events are monitor by monitor thread 
			and call interpreter's event handler function to handler the event
		*/
		
		CDocumentModule*	m_iCurrentDoc;		/**<		*/
		
		
		string				_InputChoice;
		VxmlPlatForm		_PlatForm;

		CBaseModule* CheckNext(string& next);
		TModules::iterator getNext(CBaseModule* nextDialog,TModules children);

};



#endif


