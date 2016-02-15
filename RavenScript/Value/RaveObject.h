#pragma once

namespace raven {

	class RaveObject {
	public:
		enum ObjectType {
			ARRAY_OBJECT = 1,
			STRING_OBJECT
		};
		ObjectType Type;
		bool marked;
		RaveObject();
		virtual ~RaveObject() = 0;
	};

}



