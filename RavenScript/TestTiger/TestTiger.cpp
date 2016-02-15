#include "TestTiger.h"
#include <iostream>
#include <vector>

namespace raven {

	void TestTiger::PrintMessage(const std::string& string) {
		std::cerr << "[M] " << string << std::endl;
	}

	void TestTiger::PrintInfo(const std::string& string) {
		std::cerr << "[I] " << string << std::endl;
	}

	void TestTiger::PrintError(const std::string& string) {
		std::cerr << "[E] " << string << std::endl;
	}

	struct UnitTestLink {
		TestTiger::TestProc			testProc = nullptr;
		int							errNumber = 0;
		UnitTestLink*				next = nullptr;
	};
	UnitTestLink*					testHead = nullptr;
	UnitTestLink**					testTail = &testHead;

	void TestTiger::PushTest(TestProc testProc) {
		auto link = new UnitTestLink;
		link->testProc = testProc;
		*testTail = link;
		testTail = &link->next;
	}

	void TestTiger::AddError() {
		(*testTail)->errNumber++;
	}

	void TestTiger::RunAndDisposeTests() {
		int testNumber = 0;
		int errorNumber = 0;
		std::string res = "";

		auto current = testHead;
		testHead = nullptr;
		testTail = nullptr;
		
		while (current) {
			testNumber++;
			errorNumber += current->errNumber;
			current->testProc();
			if (current->errNumber == 0) res += ".";
			else res += "F";
			auto temp = current;
			current = current->next;
			delete temp;
		}
		std::cerr << res << std::endl << "=======================" << std::endl;
		std::cerr << "Ran " << testNumber << " Tests" << std::endl;
		if (errorNumber > 0) std::cerr << "FAILED " << errorNumber << std::endl;
		else std::cerr << "OK." << std::endl;
	}
}