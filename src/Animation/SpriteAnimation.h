#pragma once

#include <string>
#include "SDL.h"
#include "Animation.h"

class SpriteAnimation : public Animation
{
    public:
        SpriteAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Draw(float x, float y, int width, int height, float xScale=1, float yScale=1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

        int GetCurrFrame(){ return m_CurrentFrame; }

        int GetCurrSpriteRow(){ return m_SpriteRow; }
        void SetSpriteRow(int row){m_SpriteRow = row; }
        void IncrSpriteRow(){m_SpriteRow++; }
        void DecrSpriteRow(){m_SpriteRow--; }

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        std::string m_TextureID;
};
