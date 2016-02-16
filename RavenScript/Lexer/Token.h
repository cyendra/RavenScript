#pragma once

#include <string>

namespace raven {

	class Token {
	public:
		Token();
		~Token();

		enum TokenType {
			NONE = 1,
			ERROR,
			END_OF_FILE,
			BOOLEAN,
			INT,
			DOUBLE,
			STRING,
			CHAR,
			IDENTIFIER
		};
		TokenType Type;

		bool GetBoolean();
		int GetInt();
		double GetDouble();
		std::string GetString();
		std::string GetIdentifier();

		void SetBoolean(bool b);
		void SetInt(int i);
		void SetDouble(double d);
		void SetString(std::string& s);
		void SetString(char* s);
		void SetIdentifier(std::string& s);
		void SetIdentifier(char* s);
		void SetChar(char c);

		static Token BooleanToken(bool b);
		static Token IntToken(int i);
		static Token DoubleToken(double d);
		static Token StringToken(std::string& s);
		static Token StringToken(char* s);
		static Token IdentifierToken(std::string& s);
		static Token IdentifierToken(char* s);
		static Token CharToken(char c);
		static Token EofToken();

	private:
		union TokenUnion {
			bool boolean_value;
			int int_value;
			double double_value;
			char char_value;
		};
		TokenUnion u;
		std::string text;
	};

}



