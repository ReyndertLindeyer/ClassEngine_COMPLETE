#include "CollisionHandler.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler * CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::Initialize(float worldSize_)
{
	previousCollisions.clear();
	previousCollisions.shrink_to_fit();

	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject * go_)
{
	scenePartition->AddObject(go_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttonType_)
{
	Ray ray = CollisionDetection::ScreenToWorldRay(mousePosition_, ClassEngine::GetInstance()->GetScreenSize());

	GameObject* hitResult = scenePartition->GetCollision(ray);
	
	if (hitResult) {
		hitResult->SetHit(true, buttonType_);
	}
	
	for (auto p : previousCollisions) {
		if (p != hitResult && p != nullptr) {
			p->SetHit(false, buttonType_);
			p = nullptr;
		}
	}

	previousCollisions.clear();

	if (hitResult) {
		previousCollisions.push_back(hitResult);
	}

	/*
	Ray collisionRay = CollisionDetection::ScreenToWorldRay(mousePosition_, ClassEngine::GetInstance()->GetScreenSize());

	float minDistance = 999999999.0f;

	for (int i = 0; i < colliders.size(); i++) {
		if (collisionRay.IsColliding(&colliders.at(i)->GetBoundingBox())) {
			if (collisionRay.intersectionDistance < minDistance) {
				minDistance = collisionRay.intersectionDistance;
					colliders[i]->SetHit(true, buttonType_);
			}
			for (int j = 0; j < previousCollisions.size(); j++) {
				if (previousCollisions[j] != colliders[i] && previousCollisions[j] != nullptr) {
					previousCollisions[j]->SetHit(false, buttonType_);
				}
			}

			previousCollisions.clear();
			previousCollisions.push_back(colliders[i]);
		}
	}*/
}

CollisionHandler::CollisionHandler()
{
}


CollisionHandler::~CollisionHandler()
{
}
