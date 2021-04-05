#pragma once

#include "Aquarius.h"
#include "Level.h"
#include "Player.h"


class LevelEditorLayer : public Aquarius::Layer
{
public:
	LevelEditorLayer();
	void onCreation() override;
	void onUpdate(Aquarius::timeDelta_t time) override;
	void onUpdateGUI(Aquarius::timeDelta_t time) override;
	void onDestruction() override;

private:
	bool m_MenuOpen = true;
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_camera;
	Aquarius::uniquePtr<Aquarius::Texture> m_spriteSheetTexture;
	Aquarius::uniquePtr<Aquarius::SpriteSheet> m_spritesheet;
	Aquarius::uniquePtr<Level> m_level;
	Aquarius::uniquePtr<Player> m_player;
	Aquarius::uniquePtr<Aquarius::Texture> m_playerTexture;
	Aquarius::uniquePtr<Aquarius::SpriteSheet> m_playerSpritesheet;
	std::unordered_map<std::string, Aquarius::QuadTexCoords> m_coordMap;
};
