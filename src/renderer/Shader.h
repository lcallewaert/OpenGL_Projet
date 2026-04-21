#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // Le constructeur lit et construit le shader
    Shader(const char *vertexPath, const char *fragmentPath);

    // Pour activer le shader
    void Use();

    // Utilitaires pour envoyer des données aux shaders (Uniforms)
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;

    unsigned int GetID();

    // Destructeur pour nettoyer la mémoire sur le GPU
    ~Shader();

private:
    // L'ID du programme final généré par le GPU
    unsigned int ID;
    // Fonction utilitaire pour vérifier les erreurs de compilation/linkage
    void CheckCompileErrors(unsigned int shader, std::string type);
};