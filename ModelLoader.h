#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

class ModelLoader {
public:
    bool isLoad(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << path << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "v") {
                glm::vec3 vertex;
                if (!parceVertices(iss, vertex)) {
                    std::cout << "Failed to parse vertex." << std::endl;
                    return false;
                }
                // Добавить вершину к модели
                vertices.push_back(vertex);
            }
            else if (type == "vt") {
                glm::vec2 textureCoord;
                if (!parceTextureCoords(iss, textureCoord)) {
                    std::cout << "Failed to parse texture coordinate." << std::endl;
                    return false;
                }
                // Добавить текстурные координаты к модели
                textureCoords.push_back(textureCoord);
            }
            else if (type == "vn") {
                glm::vec3 normal;
                if (!parceNormal(iss, normal)) {
                    std::cout << "Failed to parse normal." << std::endl;
                    return false;
                }
                // Добавить нормали к модели
                normals.push_back(normal);
            }
            else if (type == "f") {
                // Обработка индексов вершин треугольника
                // (не реализовано в данном примере)
            }
        }

        file.close();
        return true;
    }
    std::vector<glm::vec3> getVertices() {
        return vertices;
    }

    std::vector<glm::vec2> getTextureCoords() {
        return textureCoords;
    }

    std::vector<glm::vec3> getNormals() {
        return normals;
    }
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoords;
    std::vector<glm::vec3> normals;

    bool parceVertices(std::istringstream& iss, glm::vec3& vertex) {
        if (!(iss >> vertex.x >> vertex.y >> vertex.z)) {
            return false;
        }
        return true;
    }

    bool parceTextureCoords(std::istringstream& iss, glm::vec2& textureCoord) {
        if (!(iss >> textureCoord.x >> textureCoord.y)) {
            return false;
        }
        return true;
    }

    bool parceNormal(std::istringstream& iss, glm::vec3& normal) {
        if (!(iss >> normal.x >> normal.y >> normal.z)) {
            return false;
        }
        return true;
    }
    

};
