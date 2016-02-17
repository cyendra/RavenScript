#include "TestTiger\TestTiger.h"
#include "Lexer\Lexer.h"
#include "Lexer\Token.h"

#include <iostream>
#include <sstream>

TEST_CASE(TEST_LEXER) {
	using namespace raven;
	std::stringstream in;
	in << "1234 10.4 #comment fff \n ee1_23  >=  \r\n \"FFFF\"";
	Lexer lexer(&in);

	Token tInt = lexer.read();
	TEST_ASSERT(tInt.Type == Token::INT);
	TEST_PRINT_INT(tInt.GetInt());

	Token tDouble = lexer.read();
	TEST_PRINT_INT(tDouble.Type);
	TEST_ASSERT(tDouble.Type == Token::DOUBLE);

	Token tId = lexer.read();
	TEST_ASSERT(tId.Type == Token::IDENTIFIER);
	TEST_PRINT(tId.GetIdentifier());

	Token tId2 = lexer.read();
	TEST_ASSERT(tId2.Type == Token::IDENTIFIER);
	TEST_PRINT(tId2.GetIdentifier());

	Token tStr = lexer.read();
	TEST_ASSERT(tStr.Type == Token::STRING);
	TEST_PRINT(tStr.GetString());

	Token tEof = lexer.read();
	TEST_ASSERT(tEof.Type == Token::END_OF_FILE);

}