/********************************************************************************************************/
/*** MODULE INTERNAL STATE ******************************************************************************/
/********************************************************************************************************/

/*** Include header files ***/
#include "FlexActions.h"

/*** Logger ***/
static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

/*** Public function definitions ***/
void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/*** Private function declarations ***/
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/********************************************************************************************************/
/*** FLEX LEXEME ACTIONS ********************************************************************************/
/********************************************************************************************************/

/**************************************** General Lexeme Actions ****************************************/

/*** Integers ***/
Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

/*** Strings ***/
Token BeginStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return DOUBLE_QUOTES;
}
Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	printf("Matched string: %s\n", lexicalAnalyzerContext->lexeme); // Debug output
    return STRING;
}
Token EndStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return DOUBLE_QUOTES;
}

/****************************************** DSL Lexeme Actions ******************************************/

/*** CREATE_FIXTURE ***/
Token CreateFixtureLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

/*** JSON (keyword) ***/
Token BeginJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return JSON;
}

/*** SORT_BY ***/
Token SortByLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return SORT_BY;
}

/*** Dates ***/
Token StartDateLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->token = token;
    return START_DATE;
}
Token DateLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
    return DATE;
}
Token EndDateLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->token = token;
    return END_DATE;
}

/****************************************** JSON Lexeme Actions *****************************************/

/*** JSON Objects ***/
Token BeginJSONObjectLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return CURLY_BRACKET_OPEN;
}
Token ColonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return COLON;
}
Token EndJSONObjectLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return CURLY_BRACKET_CLOSE;
}

/*** JSON Comma ***/
Token CommaLexemeAction             (LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return COMMA;
}

/*** JSON Types ***/
Token JSONBoolLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = strcmp(lexicalAnalyzerContext->lexeme, "true") == 0 ? 1 : 0;
	return JSON_BOOL_TOKEN;
}
Token JSONNullLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = NULL;
	return JSON_NULL_TOKEN;
}

/************************************* Miscellaneous Lexeme Actions *************************************/

/*** Unknown Lexemes ***/
Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

/*** Ignored Lexemes ***/
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}
