//
// Created by Antonin Fruchet on 10/05/2026.
//

#include "Cube.hpp"

Cube::Cube(const sf::Vector3f& pos, const sf::Vector3f& angle, const sf::Vector3f& scale)
    : Object3D(
        pos,
        angle,
        scale
      )
{
  Cube::construct_vertices();
  Cube::construct_edges();
}

void Cube::construct_vertices() {
  const sf::Vector3f targetPos = pos;
  const sf::Vector3f targetAngle = angle;
  const sf::Vector3f targetScale = scale;

  pos = {0.f, 0.f, 0.f};
  angle = {0.f, 0.f, 0.f};
  scale = {1.f, 1.f, 1.f};

  mVertices.clear();
  mVertices.reserve(8);

  // On crée un cube de taille 1x1x1 centré sur (0,0,0)
  // Les coordonnées vont donc de -0.5 à 0.5
  float d = 0.5f;

  // Face arrière (Z = -0.5)
  mVertices.emplace_back(-d, -d, -d); // 0: Bas-Gauche-Arrière
  mVertices.emplace_back( d, -d, -d); // 1: Bas-Droite-Arrière
  mVertices.emplace_back( d,  d, -d); // 2: Haut-Droite-Arrière
  mVertices.emplace_back(-d,  d, -d); // 3: Haut-Gauche-Arrière

  // Face avant (Z = 0.5)
  mVertices.emplace_back(-d, -d,  d); // 4: Bas-Gauche-Avant
  mVertices.emplace_back( d, -d,  d); // 5: Bas-Droite-Avant
  mVertices.emplace_back( d,  d,  d); // 6: Haut-Droite-Avant
  mVertices.emplace_back(-d,  d,  d); // 7: Haut-Gauche-Avant

  rescale(targetScale);
  rotate(targetAngle);
  move(targetPos);
}

void Cube::construct_edges() {
  mEdges =  {// Face arrière
          {0, 1},
          {1, 2},
          {2, 3},
          {3, 0},
          // Face avant
          {4, 5},
          {5, 6},
          {6, 7},
          {7, 4},
          // Liaisons entre les deux faces
          {0, 4},
          {1, 5},
          {2, 6},
          {3, 7}};
}
void Cube::update(const sf::Time elapsedTime) {
  Object3D::update(elapsedTime);
  //move({0,0,0.01});
  rotate({0,1,0});
}
