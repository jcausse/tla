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

Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * SentenceProgramSemanticAction(CompilerState * compilerState, Sentence * sentence);
Initializer * createInitializerSemanticAction(int numberTourn, char * nameTourn);
Sentence * createSentenceSemanticAction(Initializer * initializer, json * json, DateRange * date_range, char * sort_by);
json * createJSONSemanticAction(json_object * json_object);
DateRange * createDateRangeSemanticAction(char * start_date, char * end_date);

json_object * createJSONObjectSemanticAction(char * key, char * value); // DEBUG ONLY
#endif
