#pragma once

#include <QObject>

//	Inherits here from qobejct just because of event, no time to implement my own event system and translate it from Qt
//	So this little hack of copying the viewport event and passing to the game thread is the best i found regarding time/efficiency.

//----------------------------------------------------------

class	Scene;
class	RenderSystem;
class	SRenderWindowData;
class	IGameWindow;

//----------------------------------------------------------

class Game final : public QObject
{
	Q_OBJECT
public:
	Game(IGameWindow *renderWindow);
	~Game();

	void					StartAndLoop();
	void					LoadScene(bool andStart = true);
	void					StartScene();

private:
	void					_ProcessRenderData();
	void					_Update(float dt);
	void					_RenderScene();
	void					_InitRenderSystem();

	float					m_Fps = 60.f;
	SRenderWindowData		*m_RenderWindowData;

	std::vector<Scene*>		m_Scenes;
	RenderSystem			*m_RenderSystem;
	IGameWindow				*m_RenderWindow;
};

//----------------------------------------------------------
