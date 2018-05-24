#include "Group.h"

Group::Group()
{
	faces = new std::vector<Face*>();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	type = NONE;
}

Group::~Group() {}

void Group::AddFace(std::vector<int>* vertexIndices, std::vector<int>* normalIndices, std::vector<int>* mappingIndices)
{
	Face* newFace = new Face(vertexIndices, normalIndices, mappingIndices);
	this->faces->push_back(newFace);
}

void Group::Bind(std::vector<GLfloat> *vertices)
{

	std::vector<GLfloat> temp = std::vector<GLfloat>(*vertices);

	if (type == NONE) {
		DefineType();
	}

	if (type != GroupType::EMPTY) {

		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices->size(), &temp[0], GL_STATIC_DRAW);

		int stride = GetStride();
		int pointerAcumulator = 0;

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);
		pointerAcumulator += 3;

		if (type == GroupType::V_T || type == GroupType::V_T_N) {
			// Texture
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid *)(pointerAcumulator * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			pointerAcumulator += 2;
		}

		if (type == GroupType::V_N || type == GroupType::V_T_N) {
			// Normal
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid *)(pointerAcumulator * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}

		glBindVertexArray(0); // Unbind VAO
	}

}

void Group::DefineType()
{
	auto tV = faces->at(0)->GetVerts()->size();
	auto tN = faces->at(0)->GetNorms()->size();
	auto tT = faces->at(0)->GetTexts()->size();

	if (tV == 0) {
		type = EMPTY;
	}
	else {
		if (tT > 0) { // Has T
			if (tN > 0) { // Has N
				type = GroupType::V_T_N;
			}
			else {
				type = GroupType::V_T;
			}
		}
		else { // No T
			if (tN > 0) { // Has N
				type = GroupType::V_N;
			}
			else { // No N
				type = GroupType::V;
			}
		}
	}
}

int Group::GetStride()
{
	switch (type)
	{
	case V:
		return 3;
	case V_T:
	case V_N:
		return 5;
	case V_T_N:
		return 8;
	}
}
