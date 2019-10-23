#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

struct BoundingBox {
public:
	glm::vec3 minVert;
	glm::vec3 maxVert;
	glm::mat4 transform;

	inline BoundingBox() {
		minVert = glm::vec3(0.0f);
		maxVert = glm::vec3(0.0f);
		transform = glm::mat4(0.0f);
	}

	inline BoundingBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::mat4 transform_) {
		minVert = minVert_;
		maxVert = maxVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 other_minCorner = GetTransformedPoint(box_->minVert, box_->transform);
		glm::vec3 other_maxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		//do aabb collision detection

		if (minCorner.x > other_maxCorner.x) return false;
		if (minCorner.y > other_maxCorner.y) return false;
		if (minCorner.z > other_maxCorner.z) return false;
		if (maxCorner.x < other_minCorner.x) return false;
		if (maxCorner.y < other_minCorner.y) return false;
		if (maxCorner.z < other_minCorner.z) return false;

		return true;
	}

private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) { 
		glm::vec3 scale; 
		glm::vec3 translation; 
		glm::vec3 skew; 
		glm::quat rotation; 
		glm::vec4 perspective;
		glm::decompose(transform_, scale, rotation, translation, skew, perspective);
		return point_ + translation;
	}
};

#endif // !BOUNDINGBOX_H
