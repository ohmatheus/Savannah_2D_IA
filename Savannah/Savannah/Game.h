#pragma once

#include <QObject>
#include "IGameController.h"

//	Inherits here from qobejct just because of events, no time to implement my own event system and translate it from Qt
//	So this little hack of copying the window events and passing to the game thread is the best i found regarding time/efficiency.

//----------------------------------------------------------

class	IScene;
class	RenderSystem;
class	SRenderWindowData;
class	IGameWindow;
class	QEvent;
class	QMouseEvent;
class	QKeyEvent;
class	QWheelEvent;
class	QSavannahMainWindow;

//----------------------------------------------------------

struct	SCamera // will have to be an entity
{
	glm::vec3	m_Position = glm::vec3(0.f, 0.f, -92.f);
	glm::vec3	m_Rotation = glm::vec3(0.f);

	glm::mat4	GetView()
	{
		glm::mat4 result = glm::mat4(1.f);

		result = glm::translate(result, m_Position);
		//result = glm::rotate(result, m_Rotation);
		return result;
	}
};

//----------------------------------------------------------

class Game final : public QObject
{
	Q_OBJECT
public:
	Game(IGameController *controller, IGameWindow *renderWindow);
	~Game();

	void					StartAndLoop();
	void					LoadScene(bool andStart = true);
	glm::mat4				View() { return m_Camera.GetView(); }
	glm::mat4				Proj() { return m_ProjMat; }
	RenderSystem			*GetRenderSystem() { return m_RenderSystem; }
	void					ProcessEvents(float dt);
	void					TooglePlayStop();

	Q_SIGNAL void			OnGamePlayStop(bool isplaying);
	Q_SIGNAL void			OnSceneParamsChanged(const SGameParameters &gameParams);

protected:
	void					KeyPressEvent(QKeyEvent *ev, float dt);
	void					KeyReleaseEvent(QKeyEvent *ev, float dt);
	void					MousePressEvent(QMouseEvent *ev, float dt);
	void					MouseReleaseEvent(QMouseEvent *ev, float dt);
	void					MouseDoubleClickEvent(QMouseEvent *ev, float dt);
	void					MouseMoveEvent(QMouseEvent *ev, float dt);
	void					WheelEvent(QWheelEvent *ev, float dt);

private:
	void					_ProcessRenderData();
	void					_Update(float dt);
	void					_RenderScene();
	void					_InitRenderSystem();
	void					_ProcessEvent(QEvent *ev, float dt);
	void					_PostEvent();
	void					_LaunchScene();
	void					_StopScene();
	void					_CheckTogglePlayStop();
	void					_GetParametersFromController();

	float					m_Fps = 60.f;
	SRenderWindowData		*m_RenderWindowData;
	glm::mat4				m_ViewProj;
	glm::mat4				m_OrthoMat;
	glm::mat4				m_ProjMat;
	SCamera					m_Camera;
	float					m_Fov = 45.f;
	float					m_SimulationSpeed = 1.f;
	bool					m_Paused = false;
	bool					m_IsGameRunning = false;
	bool					m_TogglePlayStop = false;

	std::vector<IScene*>	m_Scenes;
	IScene*					m_CurrentScene;
	RenderSystem			*m_RenderSystem;
	IGameWindow				*m_RenderWindow;
	std::vector<QEvent*>	*m_Events;
	IGameController			*m_GameController;
	SGameParameters			m_GameParameters;
	QMutex					m_UILock;
};

//----------------------------------------------------------
