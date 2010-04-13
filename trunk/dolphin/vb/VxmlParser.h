#ifndef VxmlCVxmlParser_H
#define VxmlCVxmlParser_H


#include "VbCommon.h"
#include "CVxmlModules.h"
#include "CVxmlBuilder.h"
#include "CVxmlSAXHandler.h"

/**
	@author sunyan <sunyan@hit.edu.cn>
*/
class CVxmlParser {
	/* member functions */
	public:
		/**
		* @brief Constructor
		* @note 
		*/
		CVxmlParser();
		/**
		* @brief virtual Destructor
		* @note 
		*/
		~CVxmlParser();
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
		CVxmlSAXHandler*		m_iSAXHandler;		/**<		*/
};


#endif


