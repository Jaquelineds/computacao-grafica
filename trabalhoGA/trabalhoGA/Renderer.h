#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>

#include "Mesh.h"

class Renderer {

	typedef std::map<std::string, Mesh*> MeshMap;

public:
	Renderer() {
		meshes = new MeshMap();
	}
	~Renderer() {
		delete meshes;
	}

	void Render() {

		std::vector<Group*>* currentGroups = nullptr;

		// Iterate through meshes
		for (MeshMap::iterator it = meshes->begin(); it != meshes->end(); ++it) {
			
			currentGroups = it->second->GetGroups();
			// Iterare through groups
			for (std::vector<Group*>::iterator groupIt = currentGroups->begin(); groupIt != currentGroups->end(); ++groupIt) {
				if ((*groupIt)->GetType() != GroupType::EMPTY && (*groupIt)->GetType() != GroupType::NONE) {
					glBindVertexArray((*groupIt)->VAO());
					glDrawArrays(GL_TRIANGLES, 0, (*groupIt)->GetFacesSize() * 3);
				}
			}

		}

	}

	void AssociateMesh(Mesh* mesh, std::string name) {
		if ((*meshes)[name] == nullptr) {
			(*meshes)[name] = mesh;
		}
		else {
			std::cout << "ERROR::RENDERER::NAME ALREADY TAKEN" << std::endl;
		}
	}
	void DissociateMesh(std::string name) {
		//delete (*meshes)[name];
		// Deleting would delete the mesh. We don't want that.

		(*meshes)[name] = nullptr;
	}

private:
	MeshMap* meshes;

};

#endif