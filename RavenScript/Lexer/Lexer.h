#pragma once

#include <iostream>
#include <string>
#include <deque>

#include "Token.h"

namespace raven {

	class Lexer {
	public:

		Lexer(std::istream* istream);
		~Lexer();

		Token read();
		Token peek(int i = 0);

	private:
		
		enum State {
			START,
			END,
			NUMBER,
			STRING,
			STRING_NOT_END,
			ALPHA,
			OTHER
		};
		
		std::string line;
		std::istream* in;
		std::deque<Token> deque;
		bool eof;
		std::stringstream buf;

		void getLine();

	};


}


