#ifndef ASSET_ID_H
#define ASSET_ID_H

#include <string>

class Asset_Id {
public:
	Asset_Id(const std::string& value) : m_value{value} {}
	~Asset_Id() = default;

	std::string value() const { return m_value; }
	const char* c_str() const { return m_value.c_str(); }

	static Asset_Id none() { return { "" }; }

	bool operator < (const Asset_Id& other) const { return m_value < other.value();	} // needed for std::map

private:
	std::string m_value;
};


const Asset_Id AID_Truck("truck-image");
const Asset_Id AID_Tank("tank-image");
const Asset_Id AID_Jungle("tilemap-image");
const Asset_Id AID_Tile_Map("tilemap-image");
const Asset_Id AID_Chopper("chopper-image");
const Asset_Id AID_Radar("radar-image");
const Asset_Id AID_Bullet("bullet-image");
const Asset_Id AID_Tree("tree-image");

const Asset_Id AID_Charriot_Font("charriot-font");
const Asset_Id AID_Pico8_5_Font("pico8-font-5");
const Asset_Id AID_Pico8_10_Font("pico8-font-10");

#endif // ASSET_ID_H
