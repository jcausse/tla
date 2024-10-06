%{

#include "BisonActions.h"

%}

// You touch this, and you die.
%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	char * string;
	Token token;
	json_value * json_value;

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
	Initializer * initializer;
	Sentence * sentence;
	json * json;
    json_object * json_object;

}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach. To use this mechanism, the AST must be translated into
 * another structure.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <integer> INTEGER
%token <string> STRING
%token <token> CREATE_FIXTURE
%token <token> UNKNOWN


/** Non-terminals. */
%type <program> program
%type <sentence> sentence
%type <initializer> initializer
%type <json> json
%type <json_value> json_value
%type <json_object> json_object


/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
//%left ADD SUB
//%left MUL DIV

%%

// IMPORTANT: To use λ in the following grammar, use the %empty symbol.

program: sentence	{$$ = SentenceProgramSemanticAction(currentCompilerState(), $1);}												
	;

sentence: initializer json {$$ = createSentenceSemanticAction($1, $2);}
;

initializer: CREATE_FIXTURE INTEGER STRING {$$ = createInitializerSemanticAction($2, $3);}
;

json: STRING {$$ = createJSONSemanticAction($1);}
| json_object
;

json_value:
    STRING                { 
    ;
    }
    | INTEGER               { 
       ;
    }
    | array                { ; }
    | json_object               { ; }
    ;

array:
    '[' ']'
    | '[' values ']'
    ;

values:
    json_value
    | values ',' json_value
    ;

json_object:
    '{' '}'
    | '{' members '}'
    ;

members:
    member
    | members ',' member
    ;

member:
    STRING ':' json_value
    ;



%%
