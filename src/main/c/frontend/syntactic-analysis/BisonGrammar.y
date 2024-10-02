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

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
	Initializer * initializer;
	Sentence * sentence;

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

sentence: initializer	{$$ = createSentenceSemanticAction($1);}
;

initializer: CREATE_FIXTURE INTEGER STRING {$$ = createInitializerSemanticAction($2, $3);}
;


%%
