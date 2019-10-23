#ifndef CLASSENGINE_H
#define CLASSENGINE_H

#include "Window.h"
#include "Timer.h"
#include "Debug.h"

#include "GameInterface.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Camera/Camera.h"
#include "../Rendering//3D/GameObject.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"

#include <memory>

class ClassEngine {
public:
	ClassEngine(const ClassEngine&) = delete;
	ClassEngine(ClassEngine&&) = delete;
	ClassEngine& operator=(const ClassEngine&) = delete;
	ClassEngine& operator=(ClassEngine&&) = delete;

	bool Initialize(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
	void SetGameInterface(GameInterface* gameInterface_);

	static ClassEngine* GetInstance();

	glm::vec2 GetScreenSize() const;

	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);
	void ExitGame();

private:

	ClassEngine();
	~ClassEngine();

	static std::unique_ptr<ClassEngine> engineInstance;
	friend std::default_delete<ClassEngine>;

	void Update(const float deltaTime_);
	void Render();
	void Shutdown();

	Window* window;
	Timer timer;
	GameInterface* gameInterface;

	bool isRunning;
	unsigned int fps;
};

#endif // !CLASSENGINE_H