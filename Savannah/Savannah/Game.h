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

struct	SCamera
{
	glm::vec3	m_Position = glm::vec3(0.f, 0.f, -2.f);
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
	Game(IGameWindow *renderWindow);
	~Game();

	void					StartAndLoop();
	void					LoadScene(bool andStart = true);
	void					StartScene();
	glm::mat4				View() { return m_Camera.GetView(); }
	glm::mat4				Proj() { return m_ProjMat; }

private:
	void					_ProcessRenderData();
	void					_Update(float dt);
	void					_RenderScene();
	void					_InitRenderSystem();

	float					m_Fps = 60.f;
	SRenderWindowData		*m_RenderWindowData;
	glm::mat4				m_ViewProj;
	glm::mat4				m_OrthoMat;
	glm::mat4				m_ProjMat;
	SCamera					m_Camera;
	float					m_Fov = 90.f;

	std::vector<Scene*>		m_Scenes;
	RenderSystem			*m_RenderSystem;
	IGameWindow				*m_RenderWindow;
};

//----------------------------------------------------------
