#pragma once

#include "Aquarius.h"
#include "Level.h"
#include "Player.h"
#include "Toolbar.h"


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
	float m_MoveSpeed = 0.2;
	float m_toolbarColor[4] = { 0, 0, 0, 1 };
	ToolbarAlignment m_activeItemToolbarAlignment;

	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_camera;
	Aquarius::uniquePtr<Aquarius::Texture> m_spriteSheetTexture;
	Aquarius::uniquePtr<Aquarius::SpriteSheet> m_spritesheet;
	Aquarius::uniquePtr<Level> m_level;
	Aquarius::uniquePtr<Player> m_player;
	Aquarius::uniquePtr<Aquarius::Texture> m_playerTexture;
	Aquarius::uniquePtr<Aquarius::SpriteSheet> m_playerSpritesheet;
	std::unordered_map<std::string, Aquarius::QuadTexCoords> m_coordMap;
	std::unique_ptr<Toolbar> m_activeItemToolbar;
};
