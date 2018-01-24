#ifndef WORLDOBJ_INCLUDED
#define WORLDOBJ_INCLUDED

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cstdio>
#include <iostream>

#include "Util.h"
#include "Material.h"
#include "Camera.h"

class WorldObject
{
protected:
	Vec3D world_pos;
	Vec3D size;
	int start_vertex_index;	//index where vertices start in modelData array
	int total_vertices;	//total num of vertices within modelData array
	Material mat;

public:
	//CONSTRUCTORS AND DESTRUCTORS
	WorldObject();
	WorldObject(Vec3D p);
	~WorldObject();

	//SETTERS
	void setWPosition(Vec3D p);
	void setVertStartIndex(int i);
	void setTotalVertices(int i);
	void setMaterial(Material m);
	void setSize(Vec3D s);

	//GETTERS
	Vec3D getWPosition();
	int getStartIndex();
	int getTotalVertices();
	Material getMaterial();
	Vec3D getSize();

	//OTHER
	void draw(Camera* cam, GLuint shaderProgram); //shared draw function among WObjs

	//VIRTUAL
	virtual int getType();

};



#endif
