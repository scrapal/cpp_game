#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Map/GameMap.h"
#include "Objects/GameObject.h"


#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
    public:
        static Engine* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline GameMap *GetMap() { return m_LevelMap;  }
        inline bool IsRunning() { return m_IsRunning; }
        inline SDL_Renderer *GetRenderer() { return m_Renderer; }

    private:
        Engine(){}

        GameMap *m_LevelMap;
        bool m_IsRunning;
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
        static Engine *s_Instance;

        std::vector<GameObject*> m_GameObjects;
};
