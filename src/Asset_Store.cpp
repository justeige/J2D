#include "Asset_Store.h"
#include "Logger.h"

#include <SDL.h>
#include <SDL_image.h>

Asset_Store::Asset_Store()
{
}

Asset_Store::~Asset_Store()
{
	clear_assets();
}

void Asset_Store::clear_assets()
{
	for (auto [_, texture] : m_textures) {
		SDL_DestroyTexture(texture);
	}
	m_textures.clear();
}

bool Asset_Store::add_texture(SDL_Renderer* renderer, const Asset_Id& asset_id, const std::string& file_path)
{
	auto surface = IMG_Load(file_path.c_str());
	if (!surface) { 
		Logger::err("Assets: Failed to load " + file_path);
		return false; 
	}

	auto texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture) { 
		Logger::err("Assets: Can't create texture from " + file_path);
		return false; 
	}

	m_textures.emplace(asset_id, texture);
	Logger::log("Assets: Loaded " + file_path);
	return true;
}

SDL_Texture* Asset_Store::texture(const Asset_Id& asset_id) const
{
	const auto [_, texture] = *m_textures.find(asset_id.value());
	
	return texture;
}
