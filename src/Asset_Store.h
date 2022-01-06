#ifndef ASSET_STORE_H
#define ASSET_STORE_H

#include <map>
#include "Asset_Id.h"

#include "SDL_fwd.h"

class Asset_Store {
public:
	Asset_Store();
	~Asset_Store();

	void clear_assets();
	bool add_texture(SDL_Renderer* renderer, const Asset_Id& asset_id, const std::string& file_path);
	SDL_Texture* texture(const Asset_Id& asset_id) const;

private:
	std::map<Asset_Id, SDL_Texture*> m_textures;
	// TODO fonts
	// TODO audio
};


#endif // ! ASSET_STORE_H

