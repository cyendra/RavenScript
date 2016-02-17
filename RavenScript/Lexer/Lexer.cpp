#include <cstring>
#include <sstream>

#include "Lexer.h"

namespace raven {

	Lexer::Lexer(std::istream* istream) {
		in = istream;
		eof = false;
	}


	Lexer::~Lexer() {}

	Token raven::Lexer::read() {
		Token t;
		if (fillQueue(0)) {
			t = deque.front();
			deque.pop_front();
			return t;
		}
		else {
			return Token::EofToken();
		}
	}

	Token raven::Lexer::peek(int i) {
		if (fillQueue(i)) {
			return deque.front();
		}
		else {
			return Token::EofToken();
		}
	}

	void Lexer::getLine() {
		if (in->eof()) {
			eof = true;
			deque.push_back(Token::EofToken());
			return;
		}
		std::getline(*in, line);

		State state = State::START;
		int pos = 0;
		int len = line.length();

		std::string str;
		int int_value;
		double double_value;
		char char_value;

		while (state != State::END) {
			switch (state) {
			case raven::Lexer::START:
				buf.clear();
				while (pos < len && (isspace(line[pos]))) pos++;
				if (pos >= len) state = State::END;
				else if (line[pos] == '#') state = State::COMMENT;
				else if (isdigit(line[pos])) state = State::NUMBER;
				else if (isalpha(line[pos])) state = State::ALPHA;
				else if (line[pos] == '"') state = State::STRING;
				else state = State::OTHER;
				break;
			case raven::Lexer::END:
				break;
			case raven::Lexer::NUMBER:
				while (pos < len && isdigit(line[pos])) buf << line[pos++];
				if (pos >= len || line[pos] != '.') {
					buf >> int_value;
					deque.push_back(Token::IntToken(int_value));
				}
				else if (line[pos] == '.') {
					buf << line[pos++];
					while (pos < len && isdigit(line[pos])) buf << line[pos++];
					buf >> double_value;
					deque.push_back(Token::DoubleToken(double_value));
				}
				state = State::START;
				break;
			case raven::Lexer::STRING:
				pos++;
				while (pos < len && line[pos] != '"') buf << line[pos++];
				if (pos >= len) {
					state = State::STRING_NOT_END;
				}
				else if (line[pos] == '"') {
					pos++;
					buf >> str;
					deque.push_back(Token::StringToken(str));
					state = State::START;
				}
				break;
			case raven::Lexer::STRING_NOT_END:
				while (pos < len && line[pos] != '"') buf << line[pos++];
				if (pos >= len) {
					state = State::STRING_NOT_END;
				}
				else if (line[pos] == '"') {
					pos++;
					buf >> str;
					deque.push_back(Token::StringToken(str));
					state = State::START;
				}
				break;
			case raven::Lexer::ALPHA:
				while (pos < len && (isalnum(line[pos]) || line[pos] == '_')) buf << line[pos++];
				buf >> str;
				deque.push_back(Token::IdentifierToken(str));
				state = State::START;
				break;
			case raven::Lexer::COMMENT:
				state = State::END;
				break;
			case raven::Lexer::OTHER:
				switch (line[pos]) {
				case '>':
					if (pos < len && line[pos + 1] == '=') {
						deque.push_back(Token::IdentifierToken(">="));
						pos += 2;
					}
					else {
						deque.push_back(Token::IdentifierToken(">"));
						pos += 1;
					}
					break;
				case '<':
					if (pos < len && line[pos + 1] == '=') {
						deque.push_back(Token::IdentifierToken("<="));
						pos += 2;
					}
					else {
						deque.push_back(Token::IdentifierToken("<"));
						pos += 1;
					}
				case '!':
					if (pos < len && line[pos + 1] == '=') {
						deque.push_back(Token::IdentifierToken("!="));
						pos += 2;
					}
					else {
						deque.push_back(Token::IdentifierToken("!"));
						pos += 1;
					}
				case ':':
					if (pos < len && line[pos + 1] == '=') {
						deque.push_back(Token::IdentifierToken(":="));
						pos += 2;
					}
					else {
						deque.push_back(Token::IdentifierToken(":"));
						pos += 1;
					}
				default:
					buf << line[pos];
					buf >> str;
					deque.push_back(Token::IdentifierToken(str));
					pos += 1;
					break;
				}
				state = State::START;
				break;
			default:
				throw std::exception("Lexer State Error");
				break;
			}
		}

	}

	bool Lexer::fillQueue(int i) {
		while (i >= static_cast<int>(deque.size())) {
			if (!eof) {
				getLine();
			}
			else {
				return false;
			}
		}
		return true;
	}

}