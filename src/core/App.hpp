//
// Created by Antonin Fruchet on 10/05/2026.
//

#ifndef INC_3DRENDERER_APP_H
#define INC_3DRENDERER_APP_H

#include "polygons/Cube.hpp"
#include "polygons/Object3D.hpp"
#include "polygons/Pyramid.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class App {
public:
  App();
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  void run();

  static constexpr int W_WIDTH{800};
  static constexpr int W_HEIGHT{800};

private:
  void processEvents();
  void update(sf::Time elapsedTime);
  void render();

  void updateStatistics(sf::Time elapsedTime);

  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow{sf::VideoMode({W_WIDTH, W_HEIGHT}), "SFML Application"};

  sf::Font mFont;
  std::vector<std::unique_ptr<Object3D>> mTargets;
  sf::Text mStatisticsText{mFont};
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames{0};
};



#endif //INC_3DRENDERER_APP_H
