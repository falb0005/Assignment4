/**
* \class Cube.h
* \brief A class that reperesents a Geometric cube.
* \author Justin Wilkinson
* \date April 20, 2015
*/
#pragma once

#include <GameObject.h>

struct Vertex;

class Cube : public GameObject
{
public:
  Cube();
  Cube(Vector3 position);

  void Initialize(Graphics *graphics);
  void Update(float dt);
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);
  void SetVertex(int index, float x, float y, float z, float r, float g, float b, float a);

protected:
  //void *_vertexPointer;

  Vector3 *vertices;
  Vector4 *colours;

  int size;
  int offset;

  //Vertex *vertices;
  unsigned int* indices;


};