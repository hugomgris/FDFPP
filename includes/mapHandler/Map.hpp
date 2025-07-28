#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <vector>
# include <array>
# include <stdexcept>

class Map {
	public:
		struct MapPoint {
			int z;
			int color;
			bool hasCustomColor;
			
			MapPoint(int z_val = 0, int color_val = 0, bool custom = false)
				: z(z_val), color(color_val), hasCustomColor(custom) {}
		};
		
		typedef std::vector<MapPoint> MapLine;
		
		Map();
		~Map();
		
		std::vector<MapLine> &getMapData() { return _mapData; }
		const std::vector<MapLine> &getMapData() const { return _mapData; }		
		int getWidth() const;
		int getHeight() const;
		int getZ(int x, int y) const;
		int getColor(int x, int y) const;

		bool hasCustomColor(int x, int y) const;
	
	private:
		std::vector<MapLine> _mapData;
};

#endif