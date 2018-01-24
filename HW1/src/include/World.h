#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "Vec3D.h"
#include "Camera.h"

//WorldObject classes
#include "WorldObject.h"

class World{
private:
	WorldObject** objects_array;
	int width;
	int height;
	int num_objects;
	WorldObject* floor;

	//modelData indices
	int CUBE_START = 0;
	int CUBE_VERTS = 0;
	int SPHERE_START = 0;
	int SPHERE_VERTS = 0;

public:
	//CONSTRUCTORS AND DESTRUCTORS
	World();
	World(int w, int h, int num);
	~World();

	//SETTERS
	void setCubeIndices(int start, int tris);
	void setSphereIndices(int start, int tris);

	//GETTERS
	int getWidth();
	int getHeight();

	//OTHERS
	void draw(Camera * cam, GLuint shaderProgram, GLuint uniTexID);

};

#endif
