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

%x JSON_FILENAME

%x JSON_OBJ
%x JSON_OBJ_KEY_QUOTES
%x JSON_OBJ_KEY_STRING
%x JSON_COLON
%x JSON_OBJ_VAL
%x JSON_OBJ_VAL_STRING
%x JSON_COMMA_OR_OBJ_END

%x JSON_MEMBER
%x JSON_ARRAY


/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

<INITIAL>"CREATE_FIXTURE" {
    return CreateFixtureLexemeAction(createLexicalAnalyzerContext(), CREATE_FIXTURE);
}

[[:digit:]]+ {
    return IntegerLexemeAction(createLexicalAnalyzerContext());
}

[[:space:]]+ {
    IgnoredLexemeAction(createLexicalAnalyzerContext());
}

"\"" {
    BEGIN(IN_STRING); 
    return BeginStringLexemeAction(createLexicalAnalyzerContext(), DOUBLE_QUOTES);
}
<IN_STRING>[A-Za-z0-9]* {
    return StringLexemeAction(createLexicalAnalyzerContext());
}
<IN_STRING>"\"" {
    BEGIN(INITIAL); 
    return EndStringLexemeAction(createLexicalAnalyzerContext(),DOUBLE_QUOTES);
}

"JSON" {
    BEGIN(JSON_FILENAME); 
    return BeginJSONContextLexemeAction(createLexicalAnalyzerContext(), JSON);
}
<JSON_FILENAME>([[:alnum:]_]+[[:space:]]*)*.json {
    puts("*********************************** JSON BEGIN ***********************************");
    yyin = fopen(yytext, "r");
    if (!yyin) {
        perror("Error opening file");
        exit(1);
    }
    yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
    BEGIN(JSON_OBJ);
}
<JSON_OBJ><<EOF>> {
    yypop_buffer_state();
    BEGIN(INITIAL);                 // Return to initial state after encountering JSON file EOF.
    if (!YY_CURRENT_BUFFER) {
        yyterminate(); 
    }
    puts("************************************ JSON END ************************************");
}

"SORT_BY" {
    return SortByLexemeAction(createLexicalAnalyzerContext(), SORT_BY);
}

"START_DATE" {
    return StartDateLexemeAction(createLexicalAnalyzerContext(), START_DATE);
}
"END_DATE" {
    return EndDateLexemeAction(createLexicalAnalyzerContext(), END_DATE);
}
[0-3][0-9]-[0-1][0-9]-[0-9]{2} {
    return DateLexemeAction(createLexicalAnalyzerContext());
}

. {
    return UnknownLexemeAction(createLexicalAnalyzerContext());
}



<JSON_OBJ>"{" {
    BEGIN(JSON_OBJ_KEY_QUOTES); 
    return BeginJSONObjectLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_OPEN);
}

<JSON_OBJ_KEY_QUOTES>"\"" {
    BEGIN(JSON_OBJ_KEY_STRING); 
    return BeginStringLexemeAction(createLexicalAnalyzerContext(), DOUBLE_QUOTES);
}
<JSON_OBJ_KEY_STRING>([A-Za-z0-9]|[[:space:]])* {
    return StringLexemeAction(createLexicalAnalyzerContext());
}
<JSON_OBJ_KEY_STRING>"\"" {
    BEGIN(JSON_COLON);
    return EndStringLexemeAction(createLexicalAnalyzerContext() ,DOUBLE_QUOTES);
}

<JSON_COLON>":" {
    BEGIN(JSON_OBJ_VAL); 
    return ColonLexemeAction(createLexicalAnalyzerContext(), COLON);
}

<JSON_OBJ_VAL>"\"" {
    BEGIN(JSON_OBJ_VAL_STRING);
    return BeginStringLexemeAction(createLexicalAnalyzerContext(), DOUBLE_QUOTES);
}
<JSON_OBJ_VAL_STRING>([A-Za-z0-9]|[[:space:]])* {
    return StringLexemeAction(createLexicalAnalyzerContext());
}
<JSON_OBJ_VAL_STRING>"\"" {
    BEGIN(JSON_COMMA_OR_OBJ_END);
    return EndStringLexemeAction(createLexicalAnalyzerContext() ,DOUBLE_QUOTES);
}
<JSON_OBJ_VAL>[[:digit:]]+ {
    BEGIN(JSON_COMMA_OR_OBJ_END);
    return IntegerLexemeAction(createLexicalAnalyzerContext());
}

<JSON_COMMA_OR_OBJ_END>"," {
    BEGIN(JSON_OBJ_KEY_QUOTES);
    return CommaLexemeAction(createLexicalAnalyzerContext(), COMMA);
}
<JSON_COMMA_OR_OBJ_END>"}" {
    BEGIN(JSON_OBJ);
    return EndJSONObjectLexemeAction(createLexicalAnalyzerContext(), CURLY_BRACKET_CLOSE);

}

%%

#include "FlexExport.h"
