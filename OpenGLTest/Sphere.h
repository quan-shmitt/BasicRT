#pragma once
#include <vector>
#include <windows.h>
class Sphere
{
	public:
	Sphere(float radius,  int sectorCount,  int stackCount);
	~Sphere();
	const std::vector<float>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;
	const std::vector<float>& getNormals() const;

private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

};

