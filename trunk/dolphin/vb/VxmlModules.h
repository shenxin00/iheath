#ifndef _VXML_MODULES_H_
#define _VXML_MODULES_H_


/**
* Header files
*/
#include "VbCommon.h"
#include "CBaseModule.h"


/**
* @class CDocumentModule
* @brief Document execution begins at the first dialog by default.
* As each dialog executes, it determines the next dialog.
* When a dialog doesn't specify a successor dialog, document execution stops.
*
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class CDocumentModule: public CBaseModule{
	public:
		CDocumentModule();
		virtual ~CDocumentModule();
		virtual void Accept(VxmlAbsInterpreter *interpreter);
		virtual int add(CBaseModule *child);
		virtual TModules getChild();
		int GetEventList(CEventList& pList);
		int GetDialogMap(VxmlDialogMap& pMap);
	/**
	* @ Attributes ..
	*/
	public:
		/**< @brief The version of VoiceXML of this document (required).
		* The current version number is 2.0.
		*/
		int version;
		/**< @brief The designated namespace for VoiceXML (required). 
		* The namespace for VoiceXML is defined to be http://www.w3.org/2001/vxml.
		*/
		string xmlns;
		/**< @brief The base URI for this document as defined in [XML-BASE].
		* http://www.w3.org/TR/voicexml20/#ref_XML-BASE
		* As in [HTML], a URI which all relative references within the document take as their base.
		*/
		string xml_base;
		/**< @brief The language identifier for this document .
		* If omitted, the value is a platform-specific default.
		*/
		string xml_lang;
		/**< @brief The URI of this document's application root document, if any.*/
		string application;
};


/**
* @class CMenuModule
* @brief A menu is a convenient syntactic shorthand for a form 
* which containing a single anonymous field that prompts the user to make a choice and
* transitions to different places based on that choice.
* Like a regular form, it can have its grammar scoped such that it is active when
* the user is executing another dialog.
*
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class CMenuModule : public CBaseModule
{
	public:
		CMenuModule();
		~CMenuModule();
		virtual void Accept(VxmlAbsInterpreter *interpreter);
		virtual int add(CBaseModule *child);
		virtual TModules getChild();
		PromptItemVector collectPrompts();
	/**
	* @ Attributes ..
	*/
	public:
		/**< @brief The identifier of the menu. 
		* It allows the menu to be the target of a <goto> or a <submit>.
		*/
		string id;
		/**< @brief The menu's grammar scope. 
		/* If it is dialog (the default), the menu's grammars are only active when
		* the user transitions into the menu. If the scope is document, its grammars 
		* are active over the whole document (or if the menu is in the application 
		* root document, any loaded document in the application).
		*/
		int scope;
		/**<  @brief 
		* When set to true, the first nine choices that have not explicitly specified
		* a value for the dtmf attribute are given the implicit ones "1", "2", etc.
		* Remaining choices that have not explicitly specified a value for the dtmf attribute
		* will not be assigned DTMF values (and thus cannot be matched via a DTMF keypress).
		* If there are choices which have specified their own DTMF sequences to be something 
		* other than "*", "#", or "0", an error.badfetch will be thrown. The default is false.
		*/
		bool dtmf;
		/** 			
		* When set to "exact" (the default), the text of the choice elements in the menu defines
		* the exact phrase to be recognized. When set to "approximate", the text of the choice 
		* elements defines an approximate recognition phrase (as described under Section 2.2.5).
		* Each <choice> can override this setting.
		*/
		int accept;
};

/**
* @class CPromptModule
* @brief Queue speech synthesis and audio output to the user
* The <prompt> element controls the output of synthesized speech and prerecorded audio.
* Conceptually, prompts are instantaneously queued for play, so interpretation proceeds 
* until the user needs to provide an input. At this point, the prompts are played, and
* the system waits for user input. Once the input is received from the speech recognition 
* subsystem (or the DTMF recognizer), interpretation proceeds
*
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class CPromptModule: public CBaseModule{
	public:
		CPromptModule();

		~CPromptModule();
		virtual void Accept(VxmlAbsInterpreter *interpreter);
		virtual int add(CBaseModule *child);
		virtual TModules getChild();
		string getText();
	/**
	* @ Attributes ..
	*/
	public:
	/**< @brief	Control whether a user can interrupt a prompt.
	* This defaults to the value of the bargein property. See Section 6.3.4.
	*/
	bool bargein;
	/**< @brief	Sets the type of bargein to be 'speech', or 'hotword'.
	* This defaults to the value of the bargeintype property. See Section 6.3.4.
	*/
	int bargeintype;
	/**< @brief 
	* An expression that must evaluate to true after conversion to boolean 
	* in order for the prompt to be played. Default is true.
	*/
	bool cond;
	/**< @brief 
	* A number that allows you to emit different prompts if the user is doing
	* something repeatedly. * If omitted, it defaults to "1".
	*/
	int count;
	/**< @brief 
	* The timeout that will be used for the following user input.
	*  - The value is a Time Designation (see Section 6.5). 
	*  - The default noinput timeout is platform specific.
	*/
 	int timeout;
	/**< @brief The language identifier for the prompt.
	/* If omitted, it defaults to the value specified in the document's "xml:lang" attribute.
	*/
 	
	string xml_lang;
 	/**< @brief Declares the base URI
 	* Declares the base URI from which relative URIs in the prompt are resolved.
 	* This base declaration has precedence over the <vxml> base URI declaration.
 	* If a local declaration is omitted, the value is inherited down the document hierarchy.
	*/
	string xml_base;
	
private: 

	string Text;
};

#if 0
/**
* @class VxmlObject
* @brief Interact with a custom extension
* A VoiceXML implementation platform may expose platform-specific functionality for use by a
* VoiceXML application via the <object> element. The <object> element makes direct use of its
* own content during initialization (e.g. <param> child element) and execution. As a result, 
* <object> content cannot be treated as alternative content. Notice that like other input items,
* <object> has prompts and catch elements. It may also have <filled> actions
* @author Y.Sun <sunyan@hit.edu.cn>
*/
class VxmlObject : public CBaseModule
{
	public:
		VxmlObject();

		~VxmlObject();

		virtual int add(CBaseModule* child);
		virtual TModules getChild();
		virtual void Accept(VxmlAbsInterpreter* interpreter);

	/**
	* @ Attributes ..
	*/
	public:

	/**< @brief
	* When the object is evaluated, it sets this variable to an ECMAScript value
	* whose type is defined by the object.
	*/
	string name;

	/**< @brief	The initial value of the form item variable; default is ECMAScript undefined. If initialized to a value, then the form item will not be visited unless the form item variable is cleared.
	string expr;
	/**< @brief
	An expression that must evaluate to true after conversion to boolean in order for the form item to be visited.
	*/
	string cond;
	/**< @brief The URI specifying the location of the object's implementation. The URI conventions are platform-dependent.
	*/

	string classid;
	/**< @brief The base path used to resolve relative URIs specified by classid, data, and archive. It defaults to the base URI of the current document.
	*/
	string codebase;
	/**< @brief The content type of data expected when downloading the object specified by classid. When absent it defaults to the value of the type attribute.
	*/
	int codetype;
	/**< @brief The URI specifying the location of the object's data. If it is a relative URI, it is interpreted relative to the codebase attribute.
	*/
	string data;
	/**< @brief The content type of the data specified by the data attribute.
	*/
	int type;
	/**< @brief A space-separated list of URIs for archives containing resources relevant to the object, which may include the resources specified by the classid and data attributes. URIs which are relative are interpreted relative to the codebase attribute.
	*/
	string archive;
	/**< @brief See Section 6.1. This defaults to the objectfetchhint property.
	*/
	fetchhint;
	/**< @brief See Section 6.1. This defaults to the fetchtimeout property.
	*/
	fetchtimeout;
	/**< @brief See Section 6.1. This defaults to the objectmaxage property.
	*/
	maxage;
	/**< @briefSee Section 6.1. This defaults to the objectmaxstale property.
	*/
	 maxstale;
	*/

};
#endif

    /**
    	@author Y.Sun <sunyan@hit.edu.cn>
    */
class CChoiceModule : public CBaseModule {
public:
        CChoiceModule();

        ~CChoiceModule();
        virtual void Accept(VxmlAbsInterpreter *interpreter);
        virtual int add(CBaseModule *child);
        virtual TModules getChild();
		
		
		string getChoice();
		string getNext();
private:
		string _Choice;
		string _Next;

    };



#endif 
