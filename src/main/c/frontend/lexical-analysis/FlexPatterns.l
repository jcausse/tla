%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x MULTILINE_COMMENT
%x IN_STRING

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

"\""                                {BEGIN(IN_STRING), BeginStringContextLexemeAction(createLexicalAnalyzerContext());}
<IN_STRING>"\""                     {EndStringLexemeAction(createLexicalAnalyzerContext()), BEGIN(INITIAL);}
<IN_STRING>([[:space:]][[:alnum:]])* {return StringLexemeAction(createLexicalAnalyzerContext());}

"CREATE_FIXTURE"                    { return CreateFixtureLexemeAction(createLexicalAnalyzerContext(), CREATE_FIXTURE); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
