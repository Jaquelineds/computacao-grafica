#ifndef GROUP_H
#define GROUP_H

#include <GL\glew.h>

#include <string>
#include <vector>

#include "Face.h"

enum GroupType
{
	NONE,
	EMPTY,
	V,
	V_T,
	V_N,
	V_T_N
};

class Group
{

public:

	Group();
	~Group();

	void SetName(std::string name) {
		this->name = name;
	};
	void SetMaterial(std::string material) {
		this->material = material;
	};

	std::string GetName() {
		return name;
	};
	std::string GetMaterial() {
		return material;
	};

	void AddFace(std::vector<int>* vertexIndices, std::vector<int>* normalIndices, std::vector<int>* mappingIndices);
	std::vector<Face*>* GetFaces() {
		return faces;
	}

	GLint GetFacesSize() {
		return faces->size();
	}

	void Bind(std::vector<GLfloat> *vertices);

	GLuint VAO() {
		return vbo;
	}
	GLuint VBO() {
		return vbo;
	}

	GroupType GetType() {
		return type;
	}

	void SetType(GroupType type) {
		this->type = type;
	}

	void DefineType();

private:

	std::string name;
	std::string material;

	GroupType type;

	std::vector<Face*>* faces;

	GLuint vao, vbo;


	int GetStride();

};

#endif