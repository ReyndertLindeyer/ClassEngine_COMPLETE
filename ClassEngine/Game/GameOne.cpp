#include "GameOne.h"



GameOne::GameOne()
{
}


GameOne::~GameOne()
{
}

bool GameOne::Initialize() {
	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	CollisionHandler::GetInstance()->Initialize(100.0f);
	
	Model* apple = new Model("Resources/Models/Apple/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(apple);
	Model* dice = new Model("Resources/Models/Dice/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(dice);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(apple, glm::vec3(0.0f, -4.0f, 0.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(dice, glm::vec3(3.0f, -2.0f, 0.0f)));

	return true;
}


void GameOne::Update(const float deltaTime) {
	//std::cout << "Game's Update" << std::endl;
	SceneGraph::GetInstance()->Update(deltaTime);
}


void GameOne::Render() {
	//std::cout << "Game's Render" << std::endl;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Render(Camera::GetInstance());
}