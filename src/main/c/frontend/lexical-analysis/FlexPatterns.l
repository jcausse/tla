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
%x JSON_ARRAY
%x JSON_OBJECT_STRING

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

"CREATE_FIXTURE"                    {return CreateFixtureLexemeAction(createLexicalAnalyzerContext(), CREATE_FIXTURE);}

[[:digit:]]+						{return IntegerLexemeAction(createLexicalAnalyzerContext());}

[[:space:]]+						{IgnoredLexemeAction(createLexicalAnalyzerContext());}

"\""                                {BEGIN(IN_STRING); return BeginStringContextLexemeAction(createLexicalAnalyzerContext(), DOUBLE_QUOTES);}
<IN_STRING>[A-Za-z0-9]*             {return StringLexemeAction(createLexicalAnalyzerContext());}
<IN_STRING>"\""                     {BEGIN(INITIAL); return EndStringLexemeAction(createLexicalAnalyzerContext(),DOUBLE_QUOTES);}


<JSON_OBJECT>"\""                   {BEGIN(JSON_OBJECT_STRING); return BeginStringContextLexemeAction(createLexicalAnalyzerContext(), DOUBLE_QUOTES);}
<JSON_OBJECT_STRING>[A-Za-z0-9]*    {return StringLexemeAction(createLexicalAnalyzerContext());}
<JSON_OBJECT_STRING>"\""            {BEGIN(JSON_OBJECT);return EndStringLexemeAction(createLexicalAnalyzerContext(),DOUBLE_QUOTES);}


"{"                                 {BEGIN(JSON_OBJECT); return BeginJSONObjectContextLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_OPEN);}

"JSON"                              {BEGIN(JSON); return BeginJSONContextLexemeAction(createLexicalAnalyzerContext(), JSON);}
<JSON>"}"                           {EndJSONContextLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL);}
<JSON>"{"                           {BEGIN(JSON_OBJECT); return BeginJSONObjectContextLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_OPEN);}
<JSON_OBJECT>"}"                    {BEGIN(JSON); return EndJSONObjectContextLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_CLOSE); }


<JSON_OBJECT>":"                    {return ColonLexemeAction(createLexicalAnalyzerContext(), COLON);}
<JSON_OBJECT>"{"                    {BEGIN(JSON_MEMBER); return BeginJSONMemberContextLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_OPEN);}
<JSON_MEMBER>"}"                    {BEGIN(JSON_OBJECT); return EndJSONMemberContextLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_CLOSE);}

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
    BEGIN(INITIAL);
    if (!YY_CURRENT_BUFFER) {
        yyterminate(); 
    }
}

"SORT_BY"                           {return SortByLexemeAction(createLexicalAnalyzerContext(), SORT_BY);}

"START_DATE"                        {return StartDateLexemeAction(createLexicalAnalyzerContext(), START_DATE);}

"END_DATE"                          {return EndDateLexemeAction(createLexicalAnalyzerContext(), END_DATE);}

[0-3][0-9]-[0-1][0-9]-[0-9]{2}      {return DateLexemeAction(createLexicalAnalyzerContext());}

.									{return UnknownLexemeAction(createLexicalAnalyzerContext());}



%%

#include "FlexExport.h"
