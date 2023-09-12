#pragma once
#include "cMesh.h"

class cRenderManager {
private:
	std::map<std::string, cMesh> meshes;
public:
	cRenderManager();
	~cRenderManager();

	void registerMesh( cMesh _mesh, std::string _name ) {

	}
};