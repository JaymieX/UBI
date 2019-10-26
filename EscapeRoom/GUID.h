#pragma once

namespace EscapeRoom
{
	class GameTypeGUID
	{
	public:

		using GUIDType = unsigned int;

	private:
		inline static GUIDType GetNextGUID()
		{
			static GUIDType id = 0;
			return id++;
		}

	public:
		template <typename Type>
		inline static GUIDType GetGUID()
		{
			static GUIDType type_id = GetNextGUID();
			return type_id;
		}
	};
}