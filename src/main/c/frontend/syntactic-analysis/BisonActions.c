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

Sentence * createSentenceSemanticAction(Initializer * initializer, JSONBase * json, DateRange * date_range, char * sort_by) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    Sentence * sentence = calloc(1, sizeof(Sentence));
    sentence->initializer = initializer;
    sentence->json = json;
    sentence->date_range = date_range;
    sentence->sort_by = sort_by;
    printf("\nSentence successful!\n");
    return sentence;
}


Initializer * createInitializerSemanticAction(int tournamentAmount, char * tournamentName){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Initializer * initializer = calloc(1, sizeof(Initializer));
	initializer->tournamentName = tournamentName;
	initializer->tournamentAmount = tournamentAmount;
	printf("\nInitializer Ready\n");
	return initializer;
}

JSONBase * createJSONSemanticAction(JSONKeyValuePair * kv_pair, JSONBase * next_json_base){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	JSONBase * newJson = calloc(1, sizeof(JSONBase));
	newJson->kv_pair = kv_pair;
	newJson->next_kv_pair = next_json_base;
	return newJson;
}

JSONKeyValuePair * createJSONObjectSemanticAction(char * key, JSONValue * value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	JSONKeyValuePair * new_json_kv_pair = calloc(1, sizeof(JSONKeyValuePair));
	new_json_kv_pair->key = key;
	new_json_kv_pair->value = value;
	return new_json_kv_pair;
}

JSONValue * createJSONValueSemanticAction(JSONValueType type, void * data){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	JSONValue * new_json_value = calloc(1, sizeof(JSONValue));
	new_json_value->type = type;
	switch (type){
		case JSON_STRING:
			new_json_value->value.string = (char *) data;
			break;
		case JSON_NUMBER:
		case JSON_BOOL:
			new_json_value->value.number = *((int *) data);
			break;
		case JSON_NULL:
			new_json_value->value.object = NULL;
			break;
		case JSON_ARRAY:
		case JSON_OBJECT:
			new_json_value->value.array = (struct JSONValue *) data;
			break;
	}	// TODO: ARRAYS???
	return new_json_value;
}

JSONValue * createJSONIntegerValueSemanticAction(JSONValueType type, int data){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	return createJSONValueSemanticAction(type, &data);
}

DateRange * createDateRangeSemanticAction(char * start_date, char * end_date) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    DateRange * date_range = calloc(1, sizeof(DateRange));
    date_range->start_date = strdup(start_date);
    date_range->end_date = strdup(end_date);
    return date_range;
}


JSONValue * createJSONArraySemanticAction(JSONValueArray * values) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    JSONValue * jsonValue = calloc(1, sizeof(JSONValue));
    jsonValue->type = JSON_ARRAY;
    jsonValue->value.array = values;
    return jsonValue;
}

JSONValueArray * createJSONValueArraySingleSemanticAction(JSONValue * value) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    JSONValueArray * array = calloc(1, sizeof(JSONValueArray));
    array->value = value;
    array->next = NULL;
    return array;
}

JSONValueArray * createJSONValueArraySemanticAction(JSONValue * value, JSONValueArray * next) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    JSONValueArray * array = calloc(1, sizeof(JSONValueArray));
    array->value = value;
    array->next = next;
    return array;
}
