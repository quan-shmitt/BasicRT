#include "Sphere.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include<Windows.h>

std::vector<float> vertices;
std::vector<unsigned int> indices;
std::vector<float> normals;

const float PI = 3.14159265359f;

Sphere::Sphere(float radius, int sectorCount,  int stackCount) {
	std::vector<float>().swap(vertices);
	std::vector<float>().swap(normals);
	std::vector<unsigned int>().swap(indices);
	
	float x, y, z, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i) {
		stackAngle = PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);
		for (int j = 0; j <= sectorCount; ++j) {
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);             
			y = xy * sinf(sectorAngle);             
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);
		}
	}

	int indices1, indices2;

	for (int i = 0; i <= stackCount; ++i) {
		indices1 = i * (sectorCount + 1);
		indices2 = indices1 + sectorCount + 1;
		for (int j = 0; j <= sectorCount; ++j, ++indices1, ++indices2) {
			if (i != 0) {
				indices.push_back(indices1);
				indices.push_back(indices2);
				indices.push_back(indices1 + 1);
			}

			if (i != (stackCount - 1)) {
				indices.push_back(indices1 + 1);
				indices.push_back(indices2);
				indices.push_back(indices2 + 1);
			}
		}
	}

}
Sphere::~Sphere() {
}

const std::vector<float>& Sphere::getVertices() const{
	return vertices;
}
const std::vector<unsigned int>& Sphere::getIndices() const{
	return indices;
}
const std::vector<float>& Sphere::getNormals() const{
	return normals;
}

