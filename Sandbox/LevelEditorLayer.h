#include "Aquarius.h"

class LevelEditorLayer : public Aquarius::Layer
{
public:
	LevelEditorLayer();
	void onCreation() override;
	void onUpdate(Aquarius::timeDelta_t time) override;
	void onDestruction() override;

private:
	// Map

};
