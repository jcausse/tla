#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>


/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Program * SentenceProgramSemanticAction(CompilerState * compilerState, Sentence * sentence);
Sentence * createSentenceSemanticAction(Initializer * initializer, JSONBase * json, DateRange * date_range, char * sort_by);
Initializer * createInitializerSemanticAction(int numberTourn, char * nameTourn);
JSONBase * createJSONSemanticAction(JSONKeyValuePair * kv_pair, JSONBase * next_json_base);
JSONKeyValuePair * createJSONObjectSemanticAction(char * key, JSONValue * value);
JSONValue * createJSONValueSemanticAction(JSONValueType type, void * data);
JSONValue * createJSONIntegerValueSemanticAction(JSONValueType type, int data);
DateRange * createDateRangeSemanticAction(char * start_date, char * end_date);
#endif
