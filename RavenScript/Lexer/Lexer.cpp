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
		return Token();
	}

	Token raven::Lexer::peek(int i) {
		return Token();
	}

	void Lexer::getLine() {
		if (eof) return;
		std::getline(*in, line);
		if (in->eof()) {
			eof = true;
			deque.push_back(Token::EofToken());
			return;
		}
		State state = State::START;
		int pos = 0;
		int len = line.length();
		while (state != State::END) {
			switch (state) {
			case raven::Lexer::START:
				while (pos < len && (line[pos] == ' ' || line[pos] == '\t')) pos++;
				if (pos >= len) state = State::END;
				else if (isdigit(line[pos])) state = State::NUMBER;
				else if (isalpha(line[pos])) state = State::ALPHA;
				else if (line[pos] == '"') state = State::STRING;
				else state = State::OTHER;
				break;
			case raven::Lexer::END:
				buf.clear();
				break;
			case raven::Lexer::NUMBER:
				while (pos < len && isdigit(line[pos])) buf << line[pos++];
				if (pos >= len || line[pos] != '.') {
					int num;
					buf >> num;
					deque.push_back(Token::IntToken(num));
				}
				else if (line[pos] == '.') {
					buf << line[pos++];
					while (pos < len && isdigit(line[pos])) buf << line[pos++];
					double num;
					buf >> num;
					deque.push_back(Token::DoubleToken(num));
				}
				buf.clear();
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
					std::string str;
					buf >> str;
					deque.push_back(Token::StringToken(str));
					buf.clear();
					state = State::END;
				}
				break;
			case raven::Lexer::STRING_NOT_END:
				while (pos < len && line[pos] != '"') buf << line[pos++];
				if (pos >= len) {
					state = State::STRING_NOT_END;
				}
				else if (line[pos] == '"') {
					pos++;
					std::string str;
					buf >> str;
					deque.push_back(Token::StringToken(str));
					buf.clear();
					state = State::END;
				}
				break;
			case raven::Lexer::ALPHA:
			{
				while (pos < len && line[pos] != '"') buf << line[pos++];
				std::string id;
				buf >> id;
				deque.push_back(Token::IdentifierToken(id));
				state = State::END;
				break;
			}

			case raven::Lexer::OTHER:
				break;
			default:
				break;
			}
		}

	}

}