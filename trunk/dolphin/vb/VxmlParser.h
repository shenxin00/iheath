#ifndef VxmlVxmlPARSER_H
#define VxmlVxmlPARSER_H


#include "VbCommon.h"
#include "CVxmlModules.h"
#include "CVxmlBuilder.h"
#include "VxmlSAXHandler.h"

/**
	@author sunyan <sunyan@hit.edu.cn>
*/
class VxmlParser {
	/* member functions */
	public:
		/**
		* @brief Constructor
		* @note 
		*/
		VxmlParser();
		/**
		* @brief virtual Destructor
		* @note 
		*/
		~VxmlParser();
		/**
		* @brief 
		* @note 
		* @param[in]
		* @param[in]
		* \exception 
		* \return error code
		*/
		CDocumentModule* DoParser(string& stFileUri);
		
	/* member variables */
	private:
		CVxmlBuilder*		m_iBuilder;			/**<		*/
		VxmlSAXHandler*		m_iSAXHandler;		/**<		*/
};


#endif


