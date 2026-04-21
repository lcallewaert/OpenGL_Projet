#include "Engine.h"
#include <iostream>

Engine::Engine(const std::string &title, unsigned int width, unsigned int height)
{
    // Configuration du contexte OpenGL (Version 3.3 Core)
    sf::ContextSettings settings;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;
    settings.depthBits = 24;

    m_window.create(sf::VideoMode({width, height}), title, sf::Style::Default, sf::State::Windowed, settings);
    m_window.setVerticalSyncEnabled(true);

    // Initialisation de GLEW (obligatoire après la création de la fenêtre)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Erreur : Impossible d'initialiser GLEW" << std::endl;
    }

    m_isRunning = true;

    // Activer le test de profondeur (pour la future 3D)
    glEnable(GL_DEPTH_TEST);
}

void Engine::ProcessEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_isRunning = false;
        }
    }
}

void Engine::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Display()
{
    m_window.display();
}

bool Engine::IsRunning() const
{
    return m_isRunning && m_window.isOpen();
}

Engine::~Engine()
{
    // SFML ferme la fenêtre automatiquement via son destructeur
}