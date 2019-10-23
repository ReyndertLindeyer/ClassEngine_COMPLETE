#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Graphics/TextureHandler.h"
#include <sstream>
#include <string>
#include "../../Math/BoundingBox.h"
#include "../../FX/MaterialLoader.h"

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void loadModel(const std::string& fileName_);
	void loadModel(const std::string& fileName_, const std::string& matName_);

	std::vector<Vertex> GetVerts();
	std::vector<GLuint> GetIndices();
	std::vector<SubMesh> GetMeshes();

	BoundingBox GetBoundingBox();

private:
	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void loadMaterialLibrary(const std::string matName_);
	Material currentMaterial;

	std::vector <glm::vec3> vertices;
	std::vector <glm::vec3> normals;

	std::vector <glm::vec2> textureCoords;

	std::vector <GLuint> indices;
	std::vector <GLuint> normalIndices;
	std::vector <GLuint> textureIndices;

	std::vector <Vertex> meshVertices;

	std::vector <SubMesh> meshes;

	BoundingBox boundingBox;
};
#endif // !LOADOBJMODEL_H

