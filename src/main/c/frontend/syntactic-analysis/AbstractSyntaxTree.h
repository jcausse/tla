#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

/*	DO NOT MOVE THIS (YET)	*/
typedef struct Expression Expression;
/**/

typedef struct Program Program;
typedef struct Initializer Initializer;
typedef struct Sentence Sentence;
typedef struct JSONBase JSONBase;
typedef struct JSONValue JSONValue;
typedef struct JSONKeyValuePair JSONKeyValuePair;
typedef struct DateRange DateRange;


/**
 * Node types for the Abstract Syntax Tree (AST).
 */

// TODO: Remove the Deprecated Zone

//////////JSON///////////////

struct JSONBase{
	JSONKeyValuePair * kv_pair;
	JSONBase * next_kv_pair;
};

typedef enum JSONValueType JSONValueType;
typedef struct JSONValueArray JSONValueArray;

enum JSONValueType{
	JSON_NULL, 
	JSON_BOOL,
	JSON_NUMBER, 
	JSON_STRING, 
	JSON_ARRAY, 
	JSON_OBJECT
};

struct JSONValueArray {
    JSONValue * value;
    JSONValueArray * next;
};

struct JSONValue {
    JSONValueType type;
    union {
        int number;
        char * string;
        JSONValueArray  * array; // For simplicity, pointer to the first element
        struct JSONValue * object; // Pointer to the first key-value pair
    } value;
};

struct JSONKeyValuePair{
	char * key;
	JSONValue * value;
};
//////////JSON///////////////

struct Program {
	union{
		Expression * expression;
		Sentence * sentence;
	};
};

struct Sentence{
	Initializer * initializer;
	JSONBase * json;
	char * sort_by;
	DateRange * date_range;
};

struct Initializer{
	 int tournamentAmount;
	 char * tournamentName;
};

struct DateRange {
    char * start_date;
    char * end_date;
};

/*	THE DEPRECATED ZONE	(VENTURE NO FURHTER!!)	*/
/*	Deleting any of these causes compilation to fail
	due to the backend expecting them to be present.
*/

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;

typedef struct Constant Constant;
typedef struct Factor Factor;

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

struct Constant {
	int value;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
		Initializer * initializer;
	};
	ExpressionType type;
};

/*	END OF THE DEPRECATED ZONE	*/

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);

#endif
;