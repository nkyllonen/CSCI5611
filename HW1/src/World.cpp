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

	objects_array = new WorldObject[num_objects];

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
		}
	}//END for loop

	glUniform1i(uniTexID, 1); //Set texture ID to use for floor (1 = brick texture)
	floor->draw(cam, shaderProgram);
}

//check if given pos vector collides with and WObjs in map
WorldObject* World::checkCollision(Vec3D pos)
{
	//cout << "\nChecking for collision : ";
	//pos.print();

	//check if in bounds of the map
	if (pos.getX() >= 0 &&
		pos.getZ() >= 0 &&
		pos.getX() < width*cell_width &&
		pos.getZ() < height*cell_width)
	{
		return getWO(pos);
	}

	return nullptr;
}

void World::removeWO(Vec3D pos)
{
	int i = (int)((pos.getX() - 0.5*cell_width) / cell_width);
	int j = (int)((pos.getZ() - 0.5*cell_width) / cell_width);
	objects_array[j*width + i] = new WorldObject(); //make it empty!
}

/*----------------------------*/
// PRIVATE FUNCTIONS
/*----------------------------*/
//start will start off as a green sphere
WorldObject* World::buildStart(Coord2D c)
{
	start_indices = c;

	WorldObject* start = new WO_Start(c);
	start->setVertStartIndex(SPHERE_START);
	start->setTotalVertices(SPHERE_VERTS);

	Material mat = Material();
	mat.setAmbient(glm::vec3(0, 1, 0));
	mat.setDiffuse(glm::vec3(0, 1, 0));
	mat.setSpecular(glm::vec3(0.75, 0.75, 0.75));

	start->setMaterial(mat);
	start->setSize(Vec3D(0.1, 0.1, 0.1));
	Vec3D p = getWorldPosition(c);
	start->setWPosition(p);

	return start;
}

//a wall is a white cube
WorldObject* World::buildWall(Coord2D c)
{
	WorldObject* wall = new WO_Wall(c);
	wall->setVertStartIndex(CUBE_START);
	wall->setTotalVertices(CUBE_VERTS);

	Material mat = Material();
	mat.setAmbient(glm::vec3(1, 1, 1));
	mat.setDiffuse(glm::vec3(1, 1, 1));
	mat.setSpecular(glm::vec3(0.2, 0.2, 0.2));

	wall->setMaterial(mat);
	wall->setSize(Vec3D(cell_width, cell_width, cell_width));
	wall->setWPosition(getWorldPosition(c));

	return wall;
}

//goal is a golden sphere
WorldObject* World::buildGoal(Coord2D c)
{
	WorldObject* goal = new WO_Goal(c);
	goal->setVertStartIndex(SPHERE_START);
	goal->setTotalVertices(SPHERE_VERTS);

	Material mat = Material();
	mat.setAmbient(glm::vec3(1, 0.8, 0));
	mat.setDiffuse(glm::vec3(1, 0.8, 0));
	mat.setSpecular(glm::vec3(1, 1, 1));

	goal->setMaterial(mat);
	goal->setSize(Vec3D(0.25, 0.25, 0.25));
	goal->setWPosition(getWorldPosition(c));

	return goal;
}

//key is a small cube
WorldObject* World::buildKey(Coord2D c, char ch)
{
	WorldObject* key = new WO_Key(c, ch);
	key->setVertStartIndex(CUBE_START);
	key->setTotalVertices(CUBE_VERTS);

	Material mat = Material();
	glm::vec3 color = getLetterColor(ch);
	mat.setAmbient(color);
	mat.setDiffuse(color);
	mat.setSpecular(glm::vec3(0.5, 0.5, 0.5));

	key->setMaterial(mat);
	key->setSize(cell_width*0.05*Vec3D(1,1,1));
	key->setWPosition(getWorldPosition(c));

	return key;
}

//door is a wall-sized cube
WorldObject* World::buildDoor(Coord2D c, char ch)
{
	WorldObject* door = new WO_Door(c, ch);
	door->setVertStartIndex(CUBE_START);
	door->setTotalVertices(CUBE_VERTS);

	Material mat = Material();
	glm::vec3 color = getLetterColor(ch);
	mat.setAmbient(color);
	mat.setDiffuse(color);
	mat.setSpecular(glm::vec3(0.2, 0.2, 0.2));

	door->setMaterial(mat);
	door->setSize(Vec3D(cell_width, cell_width, cell_width));
	door->setWPosition(getWorldPosition(c));

	return door;
}

//switch-case to get which color corresponds to read-in char
//for doors and keys
glm::vec3 World::getLetterColor(char ch)
{
	switch (ch)
	{
	case 'A':
	case 'a':
		return ORANGE;
	case 'B':
	case 'b':
		return BLUE;
	case 'C':
	case 'c':
		return RED;
	case 'D':
	case'd':
		return PINK;
	case 'E':
	case'e':
		return YELLOW;
	default:
		printf("\nERROR. Invalid char entered for key/door ID.\n");
		return glm::vec3(-1, -1, -1);
	}
}
