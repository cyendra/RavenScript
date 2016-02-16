#pragma once
#include "Node.h"
namespace raven {

	class Statement : Node {
	public:
		enum StatementType {
			EXPRESSION = 1,
			IF_STATEMENT,
			WHILE_STATEMENT,
			FOR_STATEMENT,
			RETURN_STATEMENT,
			BREAK_STATEMENT,
			CONTINUE_STATEMENT
		};
		Statement();
		virtual ~Statement();
	};

}


