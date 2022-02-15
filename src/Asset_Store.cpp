#include "Asset_Store.h"
#include "Logger.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

	for (auto [_, font] : m_fonts) {
		TTF_CloseFont(font);
	}
	m_fonts.clear();
}

bool Asset_Store::add_texture(SDL_Renderer* renderer, const Asset_Id& asset_id, const Str& file_path)
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

SDL_Texture* Asset_Store::texture(const Asset_Id& asset_id)
{
	return m_textures[asset_id.value()];
}

bool Asset_Store::add_font(const Asset_Id& asset_id, const Str& file_path, int font_size)
{
	auto font = TTF_OpenFont(file_path.c_str(), font_size);
	if (!font) {
		Logger::err("Assets: Failed to load " + file_path);
		return false;
	}

	m_fonts.emplace(asset_id, font);
	Logger::log("Assets: Loaded " + file_path);
	return true;
}

TTF_Font* Asset_Store::font(const Asset_Id& asset_id)
{
	return m_fonts[asset_id.value()];
}
