#include "Token.h"



raven::Token::Token() :Type(TokenType::NONE) {}

raven::Token::~Token() {}

bool raven::Token::GetBoolean() {
	return u.boolean_value;
}

int raven::Token::GetInt() {
	return u.int_value;
}

double raven::Token::GetDouble() {
	return u.double_value;
}

std::string raven::Token::GetString() {
	return text;
}

std::string raven::Token::GetIdentifier() {
	return text;
}

void raven::Token::SetBoolean(bool b) {
	Type = TokenType::BOOLEAN;
	u.boolean_value = b;
}

void raven::Token::SetInt(int i) {
	Type = TokenType::INT;
	u.int_value = i;
}

void raven::Token::SetDouble(double d) {
	Type = TokenType::DOUBLE;
	u.double_value = d;
}

void raven::Token::SetString(std::string& s) {
	Type = TokenType::STRING;
	text = s;
}

void raven::Token::SetString(char * s) {
	Type = TokenType::STRING;
	text = std::string(s);
}

void raven::Token::SetIdentifier(std::string& s) {
	Type = TokenType::IDENTIFIER;
	text = s;

}

void raven::Token::SetIdentifier(char * s) {
	Type = TokenType::IDENTIFIER;
	text = std::string(s);
}

void raven::Token::SetChar(char c) {
	Type = TokenType::CHAR;
	u.char_value = c;
}

raven::Token raven::Token::BooleanToken(bool b) {
	Token t;
	t.SetBoolean(b);
	return t;
}

raven::Token raven::Token::IntToken(int i) {
	Token t;
	t.SetInt(i);
	return t;
}

raven::Token raven::Token::DoubleToken(double d) {
	Token t;
	t.SetDouble(d);
	return t;
}

raven::Token raven::Token::StringToken(std::string & s) {
	Token t;
	t.SetString(s);
	return t;
}

raven::Token raven::Token::StringToken(char * s) {
	Token t;
	t.SetString(s);
	return t;
}

raven::Token raven::Token::IdentifierToken(std::string & s) {
	Token t;
	t.SetIdentifier(s);
	return t;
}

raven::Token raven::Token::IdentifierToken(char * s) {
	Token t;
	t.SetIdentifier(s);
	return t;
}

raven::Token raven::Token::CharToken(char c) {
	Token t;
	t.SetChar(c);
	return t;
}

raven::Token raven::Token::EofToken() {
	Token t;
	t.Type = TokenType::END_OF_FILE;
	return t;
}
