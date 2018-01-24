#include "World.h"

using namespace std;


/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
World::World()
{
	width = 0;
	height = 0;
}

World::World(int w, int h, int num)
{
	width = w;
	height = h;
	num_objects = num;

	objects_array = new WorldObject*[num_objects];

	for (int i = 0; i < num_objects; i++)
	{
		objects_array[i] = new WorldObject();
	}
}

World::~World()
{
	delete floor;

	//delete each object
	for (int i = 0; i < num_objects; i++)
	{
		delete objects_array[i];
	}

	//delete column of pointers that pointed to each row
	delete[] objects_array;
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void World::setCubeIndices(int start, int tris)
{
	CUBE_START = start;
	CUBE_VERTS = tris;
}

void World::setSphereIndices(int start, int tris)
{
	SPHERE_START = start;
	SPHERE_VERTS = tris;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
int World::getWidth()
{
	return width;
}

int World::getHeight()
{
	return height;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
//loops through WObj array and draws each
//also draws floor
void World::draw(Camera * cam, GLuint shaderProgram, GLuint uniTexID)
{
	for (int i = 0; i < width*height; i++)
	{
			glUniform1i(uniTexID, 0); //Set texture ID to use (0 = wood texture)
			objects_array[i]->draw(cam, shaderProgram);
	}//END for loop

	glUniform1i(uniTexID, 1); //Set texture ID to use for floor (1 = brick texture)
	floor->draw(cam, shaderProgram);
}

/*----------------------------*/
// PRIVATE FUNCTIONS
/*----------------------------*/
