#include "Aquarius.h"
#include "Level.h"

class LevelEditorLayer : public Aquarius::Layer
{
public:
	LevelEditorLayer();
	void onCreation() override;
	void onUpdate(Aquarius::timeDelta_t time) override;
	void onDestruction() override;

private:
	// Map
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_camera;
	Aquarius::uniquePtr<Aquarius::Texture> m_spriteSheetTexture;
	Aquarius::uniquePtr<Aquarius::SpriteSheet> m_spritesheet;
	Aquarius::uniquePtr<Level> m_level;
};
