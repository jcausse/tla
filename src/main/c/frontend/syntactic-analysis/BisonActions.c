#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}

Program * SentenceProgramSemanticAction(CompilerState * compilerState, Sentence * sentence) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->sentence = sentence;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}


Initializer * createInitializerSemanticAction(int tournamentAmount, char * tournamentName){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Initializer * initializer = calloc(1, sizeof(Initializer));
	initializer->tournamentName = tournamentName;
	initializer->tournamentAmount = tournamentAmount;
	printf("\nInitializer Ready\n");
	return initializer;
}

DateRange * createDateRangeSemanticAction(char * start_date, char * end_date) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    DateRange * date_range = calloc(1, sizeof(DateRange));
    date_range->start_date = strdup(start_date);
    date_range->end_date = strdup(end_date);
    return date_range;
}

Sentence * createSentenceSemanticAction(Initializer * initializer, json * json, DateRange * date_range, char * sort_by) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    Sentence * sentence = calloc(1, sizeof(Sentence));
    sentence->initializer = initializer;
    sentence->json = json;
    sentence->date_range = date_range;
    sentence->sort_by = sort_by;
    printf("\nSentence successful!\n");
    return sentence;
}


json * createJSONSemanticAction(json_object * json_object){
	json * newJson = calloc(1, sizeof(json));
	newJson->json_object = json_object;
	return newJson;
}

json_object * createJSONObjectSemanticAction(char * key, char * value){ //	DEBUG ONLY
	json_object * new_json_object = calloc(1, sizeof(json_object));
	new_json_object->key = key;
	new_json_object->value = value;
	return new_json_object;
}


