#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

/*** Include header files ***/
#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/*** Function declarations ***/
void initializeFlexActionsModule(); // Initialize module's internal state
void shutdownFlexActionsModule();   // Shutdown module's internal state


/********************************************************************************************************/
/*** FLEX LEXEME ACTIONS ********************************************************************************/
/********************************************************************************************************/

/**************************************** General Lexeme Actions ****************************************/

/*** Integers ***/
Token IntegerLexemeAction           (LexicalAnalyzerContext * lexicalAnalyzerContext             );

/*** Strings ***/
Token BeginStringLexemeAction       (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token StringLexemeAction            (LexicalAnalyzerContext * lexicalAnalyzerContext             );
Token EndStringLexemeAction         (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);

/****************************************** DSL Lexeme Actions ******************************************/

/*** CREATE_FIXTURE ***/
Token CreateFixtureLexemeAction     (LexicalAnalyzerContext * LexicalAnalyzerContext, Token token);

/*** JSON (keyword) ***/
Token BeginJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);

/*** SORT_BY ***/
Token SortByLexemeAction            (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);

/*** Dates ***/
Token StartDateLexemeAction         (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token DateLexemeAction              (LexicalAnalyzerContext * lexicalAnalyzerContext);
Token EndDateLexemeAction           (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);

/****************************************** JSON Lexeme Actions *****************************************/

/*** JSON Objects ***/
Token BeginJSONObjectLexemeAction   (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token ColonLexemeAction             (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token EndJSONObjectLexemeAction     (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);

/*** JSON Comma ***/
Token CommaLexemeAction             (LexicalAnalyzerContext * lexicalAnalyzerContext);

/*** JSON Types ***/
Token JSONBoolLexemeAction          (LexicalAnalyzerContext * lexicalAnalyzerContext);
Token JSONNullLexemeAction          (LexicalAnalyzerContext * lexicalAnalyzerContext);

/************************************* Miscellaneous Lexeme Actions *************************************/

/*** Unknown Lexemes ***/
Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

/*** Ignored Lexemes ***/
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif
