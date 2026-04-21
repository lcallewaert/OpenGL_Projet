#pragma once

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <string>

class Engine
{
public:
    Engine(const std::string &title, unsigned int width, unsigned int height);
    ~Engine();

    // La boucle principale
    void Run();

    // Utilitaires
    bool IsRunning() const;
    void Clear(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f);
    void Display();

    void ProcessEvents();

private:
    sf::Window m_window;
    bool m_isRunning;

    void InitOpenGL();
};