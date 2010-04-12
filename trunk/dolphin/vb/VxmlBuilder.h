#ifndef VxmlCVxmlBuilder_H
#define VxmlCVxmlBuilder_H

#include "VbCommon.h"
#include "CVxmlModules.h"

using namespace std;

/**
* local type define
*/
typedef enum EN_VXML_TAG_ID{
	//						Element						Purpose
	TAG_ID_ASSIGN,			///< < <assign>				Assign a variable a value
	TAG_ID_AUDIO,			///< < <audio>				Play an audio clip within a prompt
	TAG_ID_BLOCK,			///< < <block>				A container of (non-interactive) executable code
	TAG_ID_CATCH,			///< < <catch>				Catch an event
	TAG_ID_CHOICE,			///< < <choice>				Define a menu item
	TAG_ID_CLEAR,			///< < <clear>				Clear one or more form item variables
	TAG_ID_DISCONNECT,		///< < <disconnect>			Disconnect a session
	TAG_ID_ELSE,			///< < <else>				Used in <if> elements
	TAG_ID_ELSEIF,			///< < <elseif>				Used in <if> elements
	TAG_ID_ENUMERATE,		///< < <enumerate>			Shorthand for enumerating the choices in a menu
	TAG_ID_ERROR,			///< < <error>				Catch an error event
	TAG_ID_EXIT,			///< < <exit>				Exit a session
	TAG_ID_FIELD,			///< < <field>				Declares an input field in a form
	TAG_ID_FILLED,			///< < <filled>				An action executed when fields are filled
	TAG_ID_FORM,			///< < <form>				A dialog for presenting information and collecting data
	TAG_ID_GOTO,			///< < <goto>				Go to another dialog in the same or different document
	TAG_ID_GRAMMAR,			///< < <grammar>			Specify a speech recognition or DTMF grammar
	TAG_ID_HELP,			///< < <help>				Catch a help event
	TAG_ID_IF,				///< < <if>					Simple conditional logic
	TAG_ID_INITIAL,			///< < <initial>			Declares initial logic upon entry into a (mixed initiative) form
	TAG_ID_LINK,			///< < <link>				Specify a transition common to all dialogs in the link's scope
	TAG_ID_LOG,				///< < <log>				Generate a debug message
	TAG_ID_MENU,			///< < <menu>				A dialog for choosing amongst alternative destinations
	TAG_ID_META,			///< < <meta>				Define a metadata item as a name/value pair
	TAG_ID_METADATA,		///< < <metadata>			Define metadata information using a metadata schema
	TAG_ID_NOINPUT,			///< < <noinput>			Catch a noinput event
	TAG_ID_NOMATCH,			///< < <nomatch>			Catch a nomatch event
	TAG_ID_OBJECT,			///< < <object>				Interact with a custom extension
	TAG_ID_OPTION,			///< < <option>				Specify an option in a < <field>
	TAG_ID_PARAM,			///< < <param>				Parameter in  <object> or <subdialog>
	TAG_ID_PROMPT,			///< < <prompt>				Queue speech synthesis and audio output to the user
	TAG_ID_PROPERTY,		///< < <property>			Control implementation platform settings.
	TAG_ID_RECORD,			///< < <record>				Record an audio sample
	TAG_ID_REPROMPT,		///< < <reprompt>			Play a field prompt when a field is re-visited after an event
	TAG_ID_RETURN,			///< < <return>				Return from a subdialog.
	TAG_ID_SCRIPT,			///< < <script>				Specify a block of ECMAScript client-side scripting logic
	TAG_ID_SUBDIALOG,		///< < <subdialog>			Invoke another dialog as a subdialog of the current one
	TAG_ID_SUBMIT,			///< < <submit>				Submit values to a document server
	TAG_ID_THROW,			///< < <throw>				Throw an event.
	TAG_ID_TRANSFER,		///< < <transfer>			Transfer the caller to another destination
	TAG_ID_VALUE,			///< < <value>				Insert the value of an expression in a prompt
	TAG_ID_VAR,				///< < <var>				Declare a variable
	TAG_ID_VXML,			///< < <vxml>				Top-level element in each VoiceXML document
	TAG_NUM
}EVxmlTagID;

typedef struct ST_VXML_TAG{
	EVxmlTagID	eTagID;
	string		stTagName;
}TVxmlTag;


typedef struct ST_TAG_ATTRIBUTE{
	char*		pName;
	char*		pType;
	char*		pValue;
}TTagAttribute;

typedef map<string,int> TVxmlTagIDMap;
typedef vector<TTagAttribute> TTagAttributes;


/**
* @class CVxmlBuilder
* @brief 
*
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class CVxmlBuilder {

	/* member function */
	public:
		/**
		* @brief Constructor
		* @note 
		*/
		CVxmlBuilder();
		/**
		* @brief virtual Destructor
		* @note 
		*/
		~CVxmlBuilder();

		/**
		* @brief Build a module by tag name and attributes
		* @note 
		* @param[in] TagName
		* @param[in] Attributes
		* \exception 
		* \return error code
		*/
		int BuildElement(char* pTagName,TTagAttributes& iAttributes);
		
		
		int BuildDocument(char* value);
		
		int BuildMenu(CBaseModule* parent, char* value);
		int BuildPrompt(CBaseModule* parent, char* value);
		int BuildChoice(CBaseModule* parent, char* value);
		int BuildNoinput(CBaseModule* parent, char* value);

		CDocumentModule* getProduct();


		
	private:
		/**
		* @brief Get the enmu TagID by tagName
		* @note 
		* @param[in] TagName
		* \exception 
		* \return TagID
		*/
		int GetTagID(string& stTagName);
		/**
		* @brief Convert string to UpperCase
		* @note 
		* @param[in out ] string to convert
		* \exception 
		* \return void
		*/
		void ToUpperCase(string& str);
		/**
		* @brief Convert string to LowerCase
		* @note 
		* @param[in out ] string to convert
		* \exception 
		* \return void
		*/
		void ToLowerCase(string& str);
	/* member variables */
	private:
		CDocumentModule*	m_iVxmlDoc;			/**< The product vxml documnet's root pointer	*/
		// process variables 
		TVxmlTagIDMap		m_iVxmlTagIDMap;	/**< TagID TagName mapping collection			*/
		CBaseModule*		m_iCurrentModule;	/**< Current module to be building				*/
};


#endif

