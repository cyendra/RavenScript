#include "TestTiger.h"
#include <iostream>
#include <vector>

namespace raven {

	int TestTiger::errorNumber = 0;

	void TestTiger::PrintMessage(const std::string& string) {
		std::cerr << "[M] " << string << std::endl;
	}

	void TestTiger::PrintInfo(const std::string& string) {
		std::cerr << "[I] " << string << std::endl;
	}

	void TestTiger::PrintInfoInt(const int i) {
		std::cerr << "[I] " << i << std::endl;
	}

	void TestTiger::PrintError(const std::string& string) {
		errorNumber++;
		std::cerr << "[E] " << string << std::endl;
	}
	

	struct UnitTestLink {
		TestTiger::TestProc			testProc = nullptr;
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

	void TestTiger::RunAndDisposeTests() {
		int testNumber = 0;

		auto current = testHead;
		testHead = nullptr;
		testTail = nullptr;
		
		while (current) {
			testNumber++;
			current->testProc();
			auto temp = current;
			current = current->next;
			delete temp;
		}

		std::cerr << std::endl << "=======================" << std::endl;
		std::cerr << "Ran " << testNumber << " Tests" << std::endl;
		if (errorNumber > 0) std::cerr << "FAILED " << errorNumber << std::endl;
		else std::cerr << "OK." << std::endl;
	}
}