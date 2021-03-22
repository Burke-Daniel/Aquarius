#pragma once

#include "Aquarius/Renderer/Texture.h"

#include <array>
#include <cstdint>
#include <vector>

namespace Aquarius {

    class QuadTexCoords;
    class Texture;

    class SpriteSheet
    {
    public:
        SpriteSheet(Texture* texture, uint32_t spriteWidth, uint32_t spriteHeight);
        
        void CreateSpriteSheet(Texture* texture, uint32_t spriteWidth, uint32_t spriteHeight);

        QuadTexCoords getSpriteCoords(uint32_t i, uint32_t j) const;

        Texture* getTexture() const { return m_Texture; }

    private:
        Texture* m_Texture;
        uint32_t m_TotalWidth;
        uint32_t m_TotalHeight;
        uint32_t m_SpriteWidth;
        uint32_t m_SpriteHeight;
    };

} // namespace Aquarius
