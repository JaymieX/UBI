#pragma once

namespace EscapeRoom
{
	class Util final
	{
	public:
		template <typename Map>
		inline static bool MapContains(const Map& map_, const typename Map::key_type key_)
		{
			return map_.find(key_) != map_.end();
		}

		template <typename Map>
		inline static void MapErase(Map& map_, const typename Map::key_type key_)
		{
			map_.erase(key_);
		}
	};
}