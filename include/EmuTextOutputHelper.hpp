#pragma once 

#include <string>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "EmuInterfaceSetupHelper.hpp"

struct EmuTextOutputStyle
{
    std::string font_path;
    uint32_t font_size;
    SDL_Color text_color;
};

class EmuTextOutputHelper : public EmuInterfaceSetupHelper<const EmuTextOutputStyle&&> {
protected:
    void InterfaceSetup(const EmuTextOutputStyle&& style) override
    {
        _font.reset(TTF_OpenFont(style.font_path.c_str(), style.font_size), &TTF_CloseFont);
        if (_font.get() == nullptr)
        {
            throw std::runtime_error("Invalid font path");
        }
        _color = style.text_color;
    }

    std::shared_ptr<SDL_Texture> CreateTextTexture(const std::string& text, std::shared_ptr<SDL_Renderer> renderer)
    {
        if (_font.get() == nullptr)
        {
            return nullptr;
        }
        std::shared_ptr<SDL_Surface> surface(TTF_RenderText_Solid(_font.get(), text.c_str(), _color), SDL_FreeSurface);
        if (surface.get() == nullptr)
        {
            return nullptr;
        }
        std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), SDL_DestroyTexture);
        if (texture.get() == nullptr)
        {
            return nullptr;
        }
        return texture;
    }

    SDL_Rect GetTrueTextRectangleDim(const std::string& text)
    {
        SDL_Rect dim_rect;
        TTF_SizeText(_font.get(), text.c_str(), &dim_rect.w, &dim_rect.h);
        return dim_rect;
    }

    std::shared_ptr<TTF_Font> _font;
    SDL_Color _color;
};