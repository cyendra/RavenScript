#include "RaveValue.h"

namespace raven {
	bool RaveValue::GetBoolean() {
		return u.boolean_value;
	}
	int RaveValue::GetInt() {
		return u.int_value;
	}
	double RaveValue::GetDouble() {
		return u.double_value;
	}
	RaveNativePointer RaveValue::GetNativePointer() {
		return u.native_pointer;
	}
	RaveObject * RaveValue::GetObject() {
		return u.object;
	}
}