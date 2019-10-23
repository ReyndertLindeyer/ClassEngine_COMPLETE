#include "ClassEngine.h"

std::unique_ptr<ClassEngine> ClassEngine::engineInstance = nullptr;

void ClassEngine::NotifyOfMousePressed(int x_, int y_)
{

}

void ClassEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_)
{
	CollisionHandler::GetInstance()->Update(glm::vec2(x_, y_), buttonType_);
}

void ClassEngine::NotifyOfMouseMove(int x_, int y_)
{
	Camera::GetInstance()->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);
}

void ClassEngine::NotifyOfMouseScroll(int y_)
{
	Camera::GetInstance()->ProcessMouseZoom(y_);
}

void ClassEngine::ExitGame()
{
	isRunning = false;
}

ClassEngine::ClassEngine() : window(nullptr), isRunning(false), fps(60) {
}


ClassEngine::~ClassEngine() {
	Shutdown();
}

ClassEngine* ClassEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new ClassEngine);
	}
	return engineInstance.get();
}

glm::vec2 ClassEngine::GetScreenSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

bool ClassEngine::Initialize(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();

	if (!window->Initialize(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", __FILE__, __LINE__);
		//Shutdown();
		return isRunning = false;
	}

	//ShaderHandler::GetInstance()->CreateProgram("colorShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");
	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("baseShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	if (gameInterface) {
		if(!gameInterface->Initialize()){
			Debug::FatalError("Failed to initialize game interface", __FILE__, __LINE__);
			return isRunning = false;
		}
	}

	Debug::Info("Everything Initialized Properly", __FILE__, __LINE__);

	timer.Start();

	return isRunning = true;
}

void ClassEngine::Run() {
	while (isRunning) {
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning) {
		Shutdown();
	}
}

bool ClassEngine::GetIsRunning() {
	return isRunning;
}


void ClassEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}


void ClassEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void ClassEngine::Render() {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}

void ClassEngine::Shutdown() {
	delete window;
	window = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	SDL_Quit();
	exit(0);
}