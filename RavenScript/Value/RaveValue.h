#pragma once

#include "RaveNativePointer.h"
#include "RaveObject.h"

namespace raven {

	class RaveValue {

	public:
		static enum ValueType {
			BOOLEAN_VALUE = 1,
			INT_VALUE,
			DOUBLE_VALUE,
			STRING_VALUE,
			NATIVE_POINTER_VALUE,
			OBJECT_VALUE,
			NULL_VALUE
		};

		ValueType Type;

		bool GetBoolean();
		int GetInt();
		double GetDouble();
		RaveNativePointer GetNativePointer();
		RaveObject* GetObject();

	private:
		union ValueUnion {
			bool boolean_value;
			int int_value;
			double double_value;
			RaveNativePointer native_pointer;
			RaveObject *object;
		};
		ValueUnion u;
	};

}



