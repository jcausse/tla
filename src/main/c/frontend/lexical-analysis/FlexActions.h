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

void BeginStringContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void BeginJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndJSONContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void BeginJSONObjectContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndJSONObjectContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void BeginJSONMemberContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndJSONMemberContextLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
#endif
