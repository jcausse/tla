#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
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

/* PUBLIC FUNCTIONS */


Token BeginStringContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return DOUBLE_QUOTES;
}

Token EndStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return DOUBLE_QUOTES;
}

void BeginJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
}

void EndJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
}

Token BeginJSONObjectContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return CURLY_BRACKET_OPEN;
}

Token EndJSONObjectContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return CURLY_BRACKET_CLOSE;
}

Token BeginJSONMemberContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return CURLY_BRACKET_OPEN;
}

Token EndJSONMemberContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return CURLY_BRACKET_CLOSE;
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}




Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}


Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

Token CreateFixtureLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return STRING;
}

