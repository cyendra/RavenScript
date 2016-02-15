#pragma once

namespace raven {

	class RaveNativePointer {
	public:
		enum NativePointerInfo {
			FILE = 1
		};
	private:
		NativePointerInfo info;
		void *pointer;
	};

}

