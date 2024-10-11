#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token CreateFixtureLexemeAction(LexicalAnalyzerContext * LexicalAnalyzerContext, Token token);

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token BeginStringContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token EndStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token BeginJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
void EndJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BeginJSONObjectContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token EndJSONObjectContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token BeginJSONMemberContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token EndJSONMemberContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token JsonObjectLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ColonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
#endif
