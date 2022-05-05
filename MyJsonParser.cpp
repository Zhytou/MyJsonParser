// MyJsonParser.cpp: 定义应用程序的入口点。
//

#include "MyJsonParser.h"

namespace AtomJson
{
	class Json
	{
	public:
		typedef enum
		{
			JNULL,
			BOOL,
			NUMBER,
			OBJECT,
			ARRAY,
		} ValueType;
		Json() = default;
		void parse(const char *s);

	private:
	};
};