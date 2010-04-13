#ifndef _COM_TYPES_H_
#define _COM_TYPES_H_


/** A vxml modules's attribute						*/
typedef pair<string,string> TAttribute;
/** Vxml modules's attribute list(map)				*/
typedef map<string,string> TAttributes;
/** Linked list of VxmlModules (document sorted)	*/
typedef vector<CBaseModule*> TModules;
/** A vxml dialog									*/
typedef pair<string,string> TDialog;
/**	The vxml document's dialog collection			*/
typedef map<string,CBaseModule*> TDialogs;


/** Vxml module's type								*/
typedef enum EN_VXMLMODULE_TYPE{
	//						Element						Purpose
	TYPE_ASSIGN,			///<  <assign>				Assign a variable a value
	TYPE_AUDIO,				///<  <audio>				Play an audio clip within a prompt
	TYPE_BLOCK,				///<  <block>				A container of (non-interactive) executable code
	TYPE_CATCH,				///<  <catch>				Catch an event
	TYPE_CHOICE,			///<  <choice>				Define a menu item
	TYPE_CLEAR,				///<  <clear>				Clear one or more form item variables
	TYPE_DISCONNECT,		///<  <disconnect>			Disconnect a session
	TYPE_ELSE,				///<  <else>				Used in <if> elements
	TYPE_ELSEIF,			///<  <elseif>				Used in <if> elements
	TYPE_ENUMERATE,			///<  <enumerate>			Shorthand for enumerating the choices in a menu
	TYPE_ERROR,				///<  <error>				Catch an error event
	TYPE_EXIT,				///<  <exit>				Exit a session
	TYPE_FIELD,				///<  <field>				Declares an input field in a form
	TYPE_FILLED,			///<  <filled>				An action executed when fields are filled
	TYPE_FORM,				///<  <form>				A dialog for presenting information and collecting data
	TYPE_GOTO,				///<  <goto>				Go to another dialog in the same or different document
	TYPE_GRAMMAR,			///<  <grammar>				Specify a speech recognition or DTMF grammar
	TYPE_HELP,				///<  <help>				Catch a help event
	TYPE_IF,				///<  <if>					Simple conditional logic
	TYPE_INITIAL,			///<  <initial>				Declares initial logic upon entry into a (mixed initiative) form
	TYPE_LINK,				///<  <link>				Specify a transition common to all dialogs in the link's scope
	TYPE_LOG,				///<  <log>					Generate a debug message
	TYPE_MENU,				///<  <menu>				A dialog for choosing amongst alternative destinations
	TYPE_META,				///<  <meta>				Define a metadata item as a name/value pair
	TYPE_METADATA,			///<  <metadata>			Define metadata information using a metadata schema
	TYPE_NOINPUT,			///<  <noinput>				Catch a noinput event
	TYPE_NOMATCH,			///<  <nomatch>				Catch a nomatch event
	TYPE_OBJECT,			///<  <object>				Interact with a custom extension
	TYPE_OPTION,			///<  <option>				Specify an option in a < <field>
	TYPE_PARAM,				///<  <param>				Parameter in  <object> or <subdialog>
	TYPE_PROMPT,			///<  <prompt>				Queue speech synthesis and audio output to the user
	TYPE_PROPERTY,			///<  <property>			Control implementation platform settings.
	TYPE_RECORD,			///<  <record>				Record an audio sample
	TYPE_REPROMPT,			///<  <reprompt>			Play a field prompt when a field is re-visited after an event
	TYPE_RETURN,			///<  <return>				Return from a subdialog.
	TYPE_SCRIPT,			///<  <script>				Specify a block of ECMAScript client-side scripting logic
	TYPE_SUBDIALOG,			///<  <subdialog>			Invoke another dialog as a subdialog of the current one
	TYPE_SUBMIT,			///<  <submit>				Submit values to a document server
	TYPE_THROW,				///<  <throw>				Throw an event.
	TYPE_TRANSFER,			///<  <transfer>			Transfer the caller to another destination
	TYPE_VALUE,				///<  <value>				Insert the value of an expression in a prompt
	TYPE_VAR,				///<  <var>					Declare a variable
	TYPE_VXML,				///<  <vxml>				Top-level element in each VoiceXML document
	TYPE_TEXT,				///<  Plain Text			
//	TYPE_DOCUMENT,			///<  document				Top-level element in each VoiceXML document
	TYPE_NUM
}EModuleType;









/**************************************************/




typedef struct ST_PROMPT_ITEM {
	int _Type;
	string _Value;
}TPromptItem;






typedef list<PromptItem> PromptItemVector





#endif //_COM_TYPES_H_



