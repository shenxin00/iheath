#ifndef VxmlCVxmlInterpreter_H
#define VxmlCVxmlInterpreter_H

#include "VxmlAbsInterpreter.h"
#include "CVxmlModules.h"

#include "VxmlPlatForm.h"


/**
	@author sunyan <sunyan@hit.edu.cn>
*/
class CVxmlInterpreter
{
	/* member functions */
	public:
		/**
		* @brief Constructor
		* @note 
		*/
		CVxmlInterpreter();
		/**
		* @brief Destructor
		* @note
		*/
		~CVxmlInterpreter();
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
		CEventHandler		m_iEventHandler;	/**<		*/
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


