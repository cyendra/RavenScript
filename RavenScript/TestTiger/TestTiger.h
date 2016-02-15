#pragma once

#include <string>

namespace raven {

	class UnitTestError {};

	class TestTiger abstract {
	public:
		typedef void(*TestProc)();
		
		static void PrintMessage(const std::string& string);
		static void PrintInfo(const std::string& string);
		static void PrintError(const std::string& string);
		static void PushTest(TestProc testProc);
		static void AddError();
		static void RunAndDisposeTests();
	};

#define TEST_CHECK_ERROR(CONDITION,DESCRIPTION)												\
	do																						\
	{																						\
		if(!(CONDITION))																	\
		{																					\
			raven::TestTiger::PrintError(DESCRIPTION);										\
		}																					\
		else																				\
		{																					\
			raven::TestTiger::PrintInfo(#CONDITION);										\
		}																					\
	}while(0)

#define TEST_ASSERT(CONDITION)																\
do																							\
{																							\
	TEST_CHECK_ERROR(CONDITION,"TEST_ASSERT ERROR ON " #CONDITION);							\
}																							\
while(0)

#define TEST_ERROR(CONDITION)																\
do																							\
{																							\
	try																						\
	{																						\
		CONDITION;																			\
		throw raven::UnitTestError();														\
	}																						\
	catch(const std::exception& e)															\
	{																						\
		raven::TestTiger::PrintInfo(e.what());												\
	}																						\
	catch(const raven::UnitTestError&)														\
	{																						\
		TEST_CHECK_ERROR(false,"EXCEPTION NOT CATCH");										\
	}																						\
}while(0)

#define TEST_PRINT(x) raven::TestTiger::PrintInfo(x)

#define TEST_EXCEPTION(STATEMENT,EXCEPTION,ASSERT_FUNCTION)									\
try																							\
{																							\
	STATEMENT;																				\
	TEST_ASSERT(false,"EXCEPTION " #EXCEPTION " NOT CATCH");								\
}																							\
catch(const EXCEPTION& e)																	\
{																							\
	ASSERT_FUNCTION(e);																		\
}


#define TEST_CASE(NAME)																		\
		extern void TESTCASE_##NAME();														\
		namespace raven_testtiger_executors													\
		{																					\
			class TESTCASE_RUNNER_##NAME													\
			{																				\
			public:																			\
				static void RunUnitTest()													\
				{																			\
					raven::TestTiger::PrintMessage(#NAME);									\
					TESTCASE_##NAME();														\
				}																			\
				TESTCASE_RUNNER_##NAME()													\
				{																			\
					raven::TestTiger::PushTest(&TESTCASE_RUNNER_##NAME::RunUnitTest);		\
				}																			\
			} TESTCASE_RUNNER_##NAME##_INSTANCE;											\
		}																					\
		void TESTCASE_##NAME()


}