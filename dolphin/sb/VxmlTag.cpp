enum VxmlTagID{
	//					Element						Purpose
	ASSIGN,			///< < <assign>				Assign a variable a value
	AUDIO,			///< < <audio>				Play an audio clip within a prompt
	BLOCK,			///< < <block>				A container of (non-interactive) executable code
	CATCH,			///< < <catch>				Catch an event
	CHOICE,			///< < <choice>				Define a menu item
	CLEAR,			///< < <clear>				Clear one or more form item variables
	DISCONNECT,		///< < <disconnect>			Disconnect a session
	ELSE,			///< < <else>				Used in <if> elements
	ELSEIF,			///< < <elseif>				Used in <if> elements
	ENUMERATE,		///< < <enumerate>			Shorthand for enumerating the choices in a menu
	ERROR,			///< < <error>				Catch an error event
	EXIT,			///< < <exit>				Exit a session
	FIELD,			///< < <field>				Declares an input field in a form
	FILLED,			///< < <filled>				An action executed when fields are filled
	FORM,			///< < <form>				A dialog for presenting information and collecting data
	GOTO,			///< < <goto>				Go to another dialog in the same or different document
	GRAMMAR,		///< < <grammar>			Specify a speech recognition or DTMF grammar
	HELP,			///< < <help>				Catch a help event
	IF,				///< < <if>					Simple conditional logic
	INITIAL,		///< < <initial>			Declares initial logic upon entry into a (mixed initiative) form
	LINK,			///< < <link>				Specify a transition common to all dialogs in the link's scope
	LOG,			///< < <log>				Generate a debug message
	MENU,			///< < <menu>				A dialog for choosing amongst alternative destinations
	META,			///< < <meta>				Define a metadata item as a name/value pair
	METADATA,		///< < <metadata>			Define metadata information using a metadata schema
	NOINPUT,		///< < <noinput>			Catch a noinput event
	NOMATCH,		///< < <nomatch>			Catch a nomatch event
	OBJECT,			///< < <object>				Interact with a custom extension
	OPTION,			///< < <option>				Specify an option in a < <field>
	PARAM,			///< < <param>				Parameter in  <object> or <subdialog>
	PROMPT,			///< < <prompt>				Queue speech synthesis and audio output to the user
	PROPERTY,		///< < <property>			Control implementation platform settings.
	RECORD,			///< < <record>				Record an audio sample
	REPROMPT,		///< < <reprompt>			Play a field prompt when a field is re-visited after an event
	RETURN,			///< < <return>				Return from a subdialog.
	SCRIPT,			///< < <script>				Specify a block of ECMAScript client-side scripting logic
	SUBDIALOG,		///< < <subdialog>			Invoke another dialog as a subdialog of the current one
	SUBMIT,			///< < <submit>				Submit values to a document server
	THROW,			///< < <throw>				Throw an event.
	TRANSFER,		///< < <transfer>			Transfer the caller to another destination
	VALUE,			///< < <value>				Insert the value of an expression in a prompt
	VAR,			///< < <var>				Declare a variable
	VXML,			///< < <vxml>				Top-level element in each VoiceXML document
	TAG_NUM
};

VxmlTag VxmlTagArray[VxmlTagID::TAG_NUM] = {
	{	ASSIGN,		"ASSIGN"	},
	{	AUDIO,		"AUDIO"		},
	{	BLOCK,		"BLOCK"		},
	{	CATCH,		"CATCH"		},
	{	CHOICE,		"CHOICE"	},
	{	CLEAR,		"CLEAR"		},
	{	DISCONNECT,	"DISCONNECT"},
	{	ELSE,		"ELSE"		},
	{	ELSEIF,		"ELSEIF"	},
	{	ENUMERATE,	"ENUMERATE"	},
	{	ERROR,		"ERROR"		},
	{	EXIT,		"EXIT"		},
	{	FIELD,		"FIELD"		},
	{	FILLED,		"FILLED"	},
	{	FORM,		"FORM"		},
	{	GOTO,		"GOTO"		},
	{	GRAMMAR,	"GRAMMAR"	},
	{	HELP,		"HELP"		},
	{	IF,			"IF"		},
	{	INITIAL,	"INITIAL"	},
	{	LINK,		"LINK"		},
	{	LOG,		"LOG"		},
	{	MENU,		"MENU"		},
	{	META,		"META"		},
	{	METADATA,	"METADATA"	},
	{	NOINPUT,	"NOINPUT"	},
	{	NOMATCH,	"NOMATCH"	},
	{	OBJECT,		"OBJECT"	},
	{	OPTION,		"OPTION"	},
	{	PARAM,		"PARAM"		},
	{	PROMPT,		"PROMPT"	},
	{	PROPERTY,	"PROPERTY"	},
	{	RECORD,		"RECORD"	},
	{	REPROMPT,	"REPROMPT"	},
	{	RETURN,		"RETURN"	},
	{	SCRIPT,		"SCRIPT"	},
	{	SUBDIALOG,	"SUBDIALOG"	},
	{	SUBMIT,		"SUBMIT"	},
	{	THROW,		"THROW"		},
	{	TRANSFER,	"TRANSFER"	},
	{	VALUE,		"VALUE"		},
	{	VAR,		"VAR"		},
	{	VXML,		"VXML"		},
};


