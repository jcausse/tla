%{
#include "BisonActions.h"
%}

%define api.value.union.name SemanticValue
%union {
	/** Terminals. */
	int integer;
    int boolean;
    void * null_t;
	char * string;
	Token token;
	JSONValue * json_value_t;
	
    /** Non-terminals. */
	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
	Initializer * initializer;
	Sentence * sentence;
	JSONBase * json_t;
    JSONKeyValuePair * json_kv_pair_t;
    JSONKeyValuePair * json_array_t; //TODO: CAMBIAR el tipo
    DateRange * date_range;
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

/***********************************************************************************************/
/*** TOKENS ************************************************************************************/
/***********************************************************************************************/

/***********************/
/*** TERMINAL TOKENS ***/
/***********************/

/*** General Tokens ***/
%token <integer> INTEGER                /* Integers */
%token <string> STRING                  /* Strings */
%token <token> UNKNOWN                  /* Other unknown tokens */

/*** DSL Tokens ***/
%token <token> CREATE_FIXTURE           /* CREATE_FIXTURE */
%token <token> JSON                     /* JSON */
%token <token> SORT_BY                  /* SORT_BY */

/*** JSON Tokens ***/
%token <token> CURLY_BRACKET_OPEN       /* { */
%token <token> CURLY_BRACKET_CLOSE      /* } */
%token <token> BRACKET_OPEN             /* [ */
%token <token> BRACKET_CLOSE            /* ] */
%token <token> DOUBLE_QUOTES            /* " */
%token <token> COLON                    /* : */
%token <token> COMMA                    /* , */
%token <boolean> JSON_BOOL_TOKEN        /* true or false */
%token <null_t> JSON_NULL_TOKEN         /* null */

/*** Date Tokens ***/
%token <token> START_DATE               /* START_DATE */
%token <token> END_DATE                 /* END_DATE */
%token <string> DATE                    /* DATE */

/***************************/
/*** NON-TERMINAL TOKENS ***/
/***************************/

/*** DSL Tokens ***/
%type <program> program
%type <sentence> sentence
%type <initializer> initializer
%type <date_range> optional_date_range
%type <string> optional_sort_by

/*** JSON Tokens ***/
%type <json_t> json
%type <json_value_t> json_value
%type <json_kv_pair_t> json_kv_pair
%type <json_array_t> json_array


%%

/***********************************************************************************************/
/*** PRODUCTION RULES **************************************************************************/
/***********************************************************************************************/
/*** IMPORTANT: To use λ in the following grammar, use the %empty symbol.                    ***/

program: 
    sentence                                        { $$ = SentenceProgramSemanticAction(currentCompilerState(), $1); }
;

/**
 * Production rule: sentence
 * Any sentence starts with an initializer, followed by the "JSON" keyword, a valid json, and optional date_range and sort_by parameters.
 */
sentence: 
    initializer JSON CURLY_BRACKET_OPEN json CURLY_BRACKET_CLOSE optional_date_range optional_sort_by {
        $$ = createSentenceSemanticAction($1, $4, $6, $7); 
    }
;

/**
 * Production rule: initializer
 * An initializer is the CREATE_FIXTURE reserved word, an integer, and then a string (in between double quotes characters).
 */
initializer: 
    CREATE_FIXTURE INTEGER DOUBLE_QUOTES STRING DOUBLE_QUOTES                   { $$ = createInitializerSemanticAction($2, $4); }
;

/**
 * Production rule: json
 * Models a JSON file, consisting in curly braces with at least one json_object inside.
 */
json: 
    json_kv_pair COMMA json                                                     { $$ = createJSONSemanticAction($1, $3); }
    | json_kv_pair                                                              { $$ = createJSONSemanticAction($1, NULL); }
    | CURLY_BRACKET_OPEN json CURLY_BRACKET_CLOSE                               { $$ = createJSONSemanticAction($2->kv_pair, NULL); }
;

/**
 * Production rule: json_kv_pair
 * JSON key-value pairs separated by colons, where the KEY is always a string, and the value is any json_value.
 */
json_kv_pair:
    DOUBLE_QUOTES STRING DOUBLE_QUOTES COLON json_value                         { $$ = createJSONObjectSemanticAction($2, $5); }
;

members:
    member
    | members COMMA member
;

member:
    STRING COLON json_value
;

/**
 * Production rule: json_array
 * Matches a JSON array (either opening and closing brackets (empty array), or values in between brackets).
 */
json_array: // TODO: fix type warning
    BRACKET_OPEN BRACKET_CLOSE 
    | BRACKET_OPEN json_array_values BRACKET_CLOSE 
;

/**
 * Production rule: json_values
 * Represents values inside a JSON array. One or more values using COMMA as separator.
 */
json_array_values: 
    json_value 
    | json_value COMMA json_array_values
;

/**
 * Production rule: json_value
 * JSON values can be strings (in between double quotes), integers, arrays, or other json_object types.
 * TODO: add support for true, false, null and floating point numbers
 */
json_value:
    DOUBLE_QUOTES STRING DOUBLE_QUOTES                      { $$ = createJSONValueSemanticAction        (JSON_STRING,   $2); }
    | INTEGER                                               { $$ = createJSONIntegerValueSemanticAction (JSON_NUMBER,   $1); }
    | JSON_BOOL_TOKEN                                       { $$ = createJSONIntegerValueSemanticAction (JSON_BOOL,     $1); }
    | JSON_NULL_TOKEN                                       { $$ = createJSONValueSemanticAction        (JSON_NULL,     $1); }
    | json_array                                            { $$ = createJSONValueSemanticAction        (JSON_ARRAY,    $1); }
    | CURLY_BRACKET_OPEN json CURLY_BRACKET_CLOSE           { $$ = createJSONValueSemanticAction        (JSON_OBJECT,   $2); }
;

/* EXTRA OPTIONS MANAGEMENT SUCH AS DATE, SORT_BY... */
optional_date_range: 
    %empty                                                                      { $$ = NULL; }
    | START_DATE DATE END_DATE DATE                                             { $$ = createDateRangeSemanticAction($2, $4); }
;

optional_sort_by: 
    %empty                                                                      { $$ = NULL; }
    | SORT_BY DOUBLE_QUOTES STRING DOUBLE_QUOTES                                { $$ = $3; }
;

%%
