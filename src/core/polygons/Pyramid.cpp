//
// Created by Antonin Fruchet on 10/05/2026.
//

#include "Pyramid.hpp"

Pyramid::Pyramid(const sf::Vector3f& pos, const sf::Vector3f& angle, const sf::Vector3f& scale)
    : Object3D(
        pos,
        angle,
        scale
      )
{
  Pyramid::construct_vertices();
  Pyramid::construct_edges();
}

void Pyramid::construct_vertices() {
  const sf::Vector3f targetPos = pos;
  const sf::Vector3f targetAngle = angle;
  const sf::Vector3f targetScale = scale;

  pos = {0.f, 0.f, 0.f};
  angle = {0.f, 0.f, 0.f};
  scale = {1.f, 1.f, 1.f};

  mVertices.clear();
  mVertices.reserve(5);

  const float d = 0.5f;

  // Base carree de taille 1x1, centree sur l'origine.
  mVertices.emplace_back(-d, -d, -d); // 0: Bas-Gauche-Arriere
  mVertices.emplace_back( d, -d, -d); // 1: Bas-Droite-Arriere
  mVertices.emplace_back( d, -d,  d); // 2: Bas-Droite-Avant
  mVertices.emplace_back(-d, -d,  d); // 3: Bas-Gauche-Avant

  // Sommet de la pyramide.
  mVertices.emplace_back(0.f, d, 0.f); // 4: Sommet

  rescale(targetScale);
  rotate(targetAngle);
  move(targetPos);
}

void Pyramid::construct_edges() {
  mEdges = {
    // Base
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    // Cotes
    {0, 4},
    {1, 4},
    {2, 4},
    {3, 4}
  };
}

void Pyramid::update(const sf::Time elapsedTime) {
  Object3D::update(elapsedTime);
  rotate({0, -1, 0});
}
