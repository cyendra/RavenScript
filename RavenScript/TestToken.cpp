#include "TestTiger\TestTiger.h"
#include "Lexer\Token.h"

TEST_CASE(TEST_TOKEN) {
	TEST_PRINT_INT(sizeof(raven::Token));
	raven::Token t;
	TEST_ASSERT(t.Type == raven::Token::NONE);
	t.SetString("ddd");
	TEST_ASSERT(t.GetString() == "ddd");
}