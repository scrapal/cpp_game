#pragma once

#include <string>
#include "SDL.h"

class Animation
{
    public:
        Animation() {}
        
        void Update();
        void Draw(float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        int m_CurrentFrame;
        std::string m_TextureID;
};