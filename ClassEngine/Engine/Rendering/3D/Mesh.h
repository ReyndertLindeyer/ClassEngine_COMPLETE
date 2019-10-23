#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Core/Debug.h"
#include "../../Graphics//MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<GLuint> indices;
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4> instances_);

private:
	GLuint VAO, VBO;
	void GenerateBuffers();
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint viewPositionLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColorLoc;
	GLuint diffuseMapLoc, shininessLoc, transparencyLoc, ambientLoc, diffuseLoc, specularLoc;
};


#endif // MESH_H