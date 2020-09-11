// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {

	static int GetCode(const zSTRING& str)
	{
		int code = 0;
		for (int i = 0; i < str.Length(); i++)
		{
			code = code + (i * 11) * int(str[i]);
		};
		return code;
	};

}