#pragma once

#include "Character.h"
#include "Animation/Animation.h"
#include "Physics/RigidBody.h"

class Warrior : public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        // int m_Row, m_Frame, m_FrameCount;
        // int m_AnimSpeed;

        Animation *m_Animation;
        RigidBody *m_RigidBody;
};