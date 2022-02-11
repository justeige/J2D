#ifndef ASSET_STORE_H
#define ASSET_STORE_H

#include <JUL/Container.h>
#include "Asset_Id.h"
#include "SDL_fwd.h"

class Asset_Store {
public:
	Asset_Store();
	~Asset_Store();

	void clear_assets();

	bool add_texture(SDL_Renderer* renderer, const Asset_Id& asset_id, const Str& file_path);
	SDL_Texture* texture(const Asset_Id& asset_id);

	void add_font(const Asset_Id& asset_id, const Str& file_path, int font_size);
	TTF_Font* font(const Asset_Id& asset_id);

private:
	// TODO use Data ptr
	Map<Asset_Id, SDL_Texture*> m_textures;
	Map<Asset_Id, TTF_Font*> m_fonts;
	// TODO audio
};


#endif // ! ASSET_STORE_H

