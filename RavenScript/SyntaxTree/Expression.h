#pragma once

#include "Statement.h"

namespace raven {

	class Expression : Statement {
	public:
		enum ExpressionType {
			BOOLEAN = 1,
			INT,
			DOUBLE,
			STRING,
			IDENTIFIER,
			ADD,
			SUB,
			MUL,
			DIV,
			MOD,
			EQ,
			NE,
			GT,
			GE,
			LT,
			LE,
			LOGICAL_AND,
			LOGICAL_OR,
			LOGICAL_NOT,
			MINUS,
			FUNCTION_CALL,
			NULL
		};
		Expression();
		virtual ~Expression();
	};

}



