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
/* " */
%token <token> DOUBLE_QUOTES
/* { */
%token <token> CURLY_BRACKET_OPEN
/* } */
%token <token> CURLY_BRACKET_CLOSE
/* [ */
%token <token> BRACKET_OPEN 
/* ] */
%token <token> BRACKET_CLOSE
/* JSON */
%token <token> JSON
/*:*/
%token <token> COLON
/*SORT_BY*/
%token <token> SORT_BY

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

//  "key":"value"
json_object: DOUBLE_QUOTES STRING DOUBLE_QUOTES COLON DOUBLE_QUOTES STRING DOUBLE_QUOTES {$$ = createJSONObjectSemanticAction($2, $6);}
    ;

json: CURLY_BRACKET_OPEN json_object CURLY_BRACKET_CLOSE{$$ = createJSONSemanticAction($2);}
;


sentence: initializer JSON json SORT_BY DOUBLE_QUOTES STRING DOUBLE_QUOTES{
    $$ = createSentenceSemanticAction($1, $3, $6);
    | /*SENTENCE CON MENOS COSAS*/
}
;


initializer: CREATE_FIXTURE INTEGER DOUBLE_QUOTES STRING DOUBLE_QUOTES 
{$$ = createInitializerSemanticAction($2, $4);}
;



members:
    member
    | members ',' member
    ;

member:
    STRING ':' json_value
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



%%
