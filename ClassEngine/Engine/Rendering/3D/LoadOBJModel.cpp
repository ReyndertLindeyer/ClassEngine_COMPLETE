#include "LoadOBJModel.h"



LoadOBJModel::LoadOBJModel() : currentMaterial(Material())
{
}


LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	vertices.shrink_to_fit();

	normals.clear();
	normals.shrink_to_fit();

	textureCoords.clear();
	textureCoords.shrink_to_fit();

	indices.clear();
	indices.shrink_to_fit();

	normalIndices.clear();
	normalIndices.shrink_to_fit();

	textureIndices.clear();
	textureIndices.shrink_to_fit();

	meshVertices.clear();
	meshVertices.shrink_to_fit();

	meshes.clear();
	meshes.shrink_to_fit();
}

void LoadOBJModel::loadModel(const std::string & fileName_)
{
	std::ifstream in(fileName_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot Open OBJ file: " + fileName_, __FILE__, __LINE__);
		return;
	}

	boundingBox.minVert.x = 999.9f;
	boundingBox.minVert.y = 999.9f;
	boundingBox.minVert.z = 999.9f;

	std::string line;
	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			double x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			if (boundingBox.minVert.x > x) {
				boundingBox.minVert.x = x;
			}
			if (boundingBox.maxVert.x < x) {
				boundingBox.maxVert.x = x;
			}

			if (boundingBox.minVert.y > y) {
				boundingBox.minVert.y = y;
			}
			if (boundingBox.maxVert.y < y) {
				boundingBox.maxVert.y = y;
			}

			if (boundingBox.minVert.z > z) {
				boundingBox.minVert.z = z;
			}
			if (boundingBox.maxVert.z < z) {
				boundingBox.maxVert.z = z;
			}

			/*Important for checking clicking stuff
			(max x, max y, max z)
			(max x, min y, max z)
			(min x, max y, max z)
			(min x, min y, max z)
			(max x, max y. min z)
			(max x, min y, min z)
			(min x, max y, min z)
			(min x, min y, min z)
			*/

			//std::cout << "The vertex data is x: " << x << " y: " << y << " z: " << z;
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream v(line.substr(3));
			double x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));

			//std::cout << "The normal data is x: " << x << " y: " << y << " z: " << z;
		}

		//TEXTURE COORDINATE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::istringstream v(line.substr(3));
			double a, b, c;
			v >> a >> b >> c;
			textureCoords.push_back(glm::vec2(a, b));

			//std::cout << "The texture coordinate data is a: " << a << " b: " << b << " c: " << c;
		}

		//FACE DATA
		///(position/texture/normal)
		else if (line.substr(0, 2) == "f ") {
			std::istringstream v(line.substr(2));

			int temp;
			char z;

			for (int i = 0; i < 3; i++) {
				v >> temp;
				indices.push_back(temp);
				v >> z;

				v >> temp;
				textureIndices.push_back(temp);
				v >> z;

				v >> temp;
				normalIndices.push_back(temp);
			}
		}

		//MATERIAL DATA
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::loadModel(const std::string & fileName_, const std::string & matName_)
{
	loadMaterialLibrary(matName_);
	loadModel(fileName_);
}

std::vector<Vertex> LoadOBJModel::GetVerts()
{
	return meshVertices;
}

std::vector<GLuint> LoadOBJModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetMeshes()
{
	return meshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.texCoords = textureCoords[textureIndices[i] - 1];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;

	mesh.vertexList = meshVertices;
	mesh.indices = indices;
	mesh.material = currentMaterial;

	meshes.push_back(mesh);

	indices.clear();
	indices.shrink_to_fit();

	normalIndices.clear();
	normalIndices.shrink_to_fit();

	textureIndices.clear();
	textureIndices.shrink_to_fit();

	meshVertices.clear();
	meshVertices.shrink_to_fit();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string & fileName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::loadMaterialLibrary(const std::string matName_)
{
	MaterialLoader::LoadMaterial(matName_);
}
