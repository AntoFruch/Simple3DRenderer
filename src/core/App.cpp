//
// Created by Antonin Fruchet on 10/05/2026.
//

#include "App.hpp"

#include <iostream>

const sf::Time App::TimePerFrame = sf::seconds(1.f / 60.f);

App::App() {
  assert(mFont.openFromFile("res/Sansation.ttf"));
  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);

  mTargets.push_back(std::make_unique<Cube>(
    sf::Vector3f{0.F,0.F,1.F},
    //sf::Vector3f{0.F, 0.F, 0.F},
    sf::Vector3f{45.F, 0.F, 45.F},
    sf::Vector3f{0.5F,0.5F,0.5F}
  ));

  mTargets.push_back(std::make_unique<Pyramid>(
    sf::Vector3f{0.7F, 0.F, 1.6F},
    sf::Vector3f{20.F, 30.F, 0.F},
    sf::Vector3f{0.5F, 0.7F, 0.5F}
  ));
}

void App::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  mWindow.setVerticalSyncEnabled(true);
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processEvents();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
    render();
  }
}

void App::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}


void App::update(const sf::Time elapsedTime) {
  for (auto& target : mTargets) {
    target->update(elapsedTime);
  }
}

void App::render() {
  mWindow.clear();
  for (const auto& target : mTargets) {
    target->draw(mWindow);
  }
  mWindow.draw(mStatisticsText);
  mWindow.display();
}

void App::updateStatistics(const sf::Time elapsedTime) {
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;

  if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
    mStatisticsText.setString(std::format(
        "Frames / Second = {}\nTime / Update = {} us", mStatisticsNumFrames,
        mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames));

    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
}
