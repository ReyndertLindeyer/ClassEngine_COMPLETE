#ifndef GAME_H
#define GAME_H

#include "../Engine/Core/ClassEngine.h"
#include <glm/gtx/string_cast.hpp>


class GameOne : public GameInterface
{
public:
	GameOne();
	virtual ~GameOne();

	virtual bool Initialize();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:

};


#endif // !GAME_H


