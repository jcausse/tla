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
%x IN_STRING
%x JSON
%x JSON_OBJECT
%x JSON_MEMBER

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

<IN_STRING>"\""                     {EndStringLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL);}
"\""                                {BEGIN(IN_STRING); BeginStringContextLexemeAction(createLexicalAnalyzerContext());}
<IN_STRING>([[:alnum:]][[:space:]]*)* {return StringLexemeAction(createLexicalAnalyzerContext());}

"JSON"                              {BEGIN(JSON); BeginJSONContextLexemeAction(createLexicalAnalyzerContext());}

"{"                                 {BEGIN(JSON_OBJECT); BeginJSONObjectContextLexemeAction(createLexicalAnalyzerContext()); }
<JSON>"}"                           {BEGIN(INITIAL); EndJSONContextLexemeAction(createLexicalAnalyzerContext());}
<JSON>"{"                           {BEGIN(JSON_OBJECT); BeginJSONObjectContextLexemeAction(createLexicalAnalyzerContext()); }
<JSON_OBJECT>"}"                    {EndJSONObjectContextLexemeAction(createLexicalAnalyzerContext()); BEGIN(JSON);}

<JSON_OBJECT>"{"                    {BEGIN(JSON_MEMBER); BeginJSONMemberContextLexemeAction(createLexicalAnalyzerContext());}
<JSON_MEMBER>"}"                    {BEGIN(JSON_OBJECT); EndJSONMemberContextLexemeAction(createLexicalAnalyzerContext());}

<JSON>([[:alnum:]_]+[[:space:]]*)*.json {
    yyin = fopen(yytext, "r");
    if (!yyin) {
        perror("Error opening file");
        exit(1);
    }
    yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
    BEGIN(INITIAL); 
}

<<EOF>> {
    yypop_buffer_state();
    if (!YY_CURRENT_BUFFER) {
        yyterminate(); 
    }
}


"CREATE_FIXTURE"                    { return CreateFixtureLexemeAction(createLexicalAnalyzerContext(), CREATE_FIXTURE); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }


.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
