#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

//class ModelLoader {
//public:
//    bool isLoad(const std::string& path) {
//        std::ifstream file(path);
//        if (!file.is_open()) {
//            std::cout << "Failed to open file: " << path << std::endl;
//            return false;
//        }
//
//        std::string line;
//        while (std::getline(file, line)) {
//            std::istringstream iss(line);
//            std::string type;
//            iss >> type;
//
//            if (type == "v") {
//                glm::vec3 vertex;
//                if (!parseVertices(iss, vertex)) {
//                    std::cout << "Failed to parse vertex." << std::endl;
//                    return false;
//                }
//                // Добавить вершину к модели
//                vertices.push_back(vertex);
//            }
//            else if (type == "vt") {
//                glm::vec2 textureCoord;
//                if (!parseTextureCoords(iss, textureCoord)) {
//                    std::cout << "Failed to parse texture coordinate." << std::endl;
//                    return false;
//                }
//                // Добавить текстурные координаты к модели
//                textureCoords.push_back(textureCoord);
//            }
//            else if (type == "vn") {
//                glm::vec3 normal;
//                if (!parseNormal(iss, normal)) {
//                    std::cout << "Failed to parse normal." << std::endl;
//                    return false;
//                }
//                // Добавить нормали к модели
//                normals.push_back(normal);
//            }
//            else if (type == "f") {
//                std::vector<int> vertexIndices, textureCoordIndices, normalIndices;
//                if (!parseFaceIndices(iss, vertexIndices, textureCoordIndices, normalIndices)) {
//                    std::cout << "Failed to parse face indices." << std::endl;
//                    return false;
//                }
//                // Обработка индексов вершин треугольника
//                for (int i = 0; i < vertexIndices.size(); i++) {
//                    int vertexIndex = vertexIndices[i] - 1;
//                    int textureCoordIndex = textureCoordIndices[i] - 1;
//                    int normalIndex = normalIndices[i] - 1;
//                    // Добавить индексы к модели
//                    // ...
//                }
//            }
//        }
//
//        file.close();
//        return true;
//    }
//    std::vector<glm::vec3> getVertices() {
//        return vertices;
//    }
//
//    std::vector<glm::vec2> getTextureCoords() {
//        return textureCoords;
//    }
//
//    std::vector<glm::vec3> getNormals() {
//        return normals;
//    }
//private:
//    std::vector<glm::vec3> vertices;
//    std::vector<glm::vec2> textureCoords;
//    std::vector<glm::vec3> normals;
//
//    bool parseVertices(std::istringstream& iss, glm::vec3& vertex) {
//        if (!(iss >> vertex.x >> vertex.y >> vertex.z)) {
//            return false;
//        }
//        return true;
//    }
//
//    bool parseTextureCoords(std::istringstream& iss, glm::vec2& textureCoord) {
//        if (!(iss >> textureCoord.x >> textureCoord.y)) {
//            return false;
//        }
//        return true;
//    }
//
//    bool parseNormal(std::istringstream& iss, glm::vec3& normal) {
//        if (!(iss >> normal.x >> normal.y >> normal.z)) {
//            return false;
//        }
//        return true;
//    }
//
//    bool parseFaceIndices(std::istringstream& iss, std::vector<int>& vertexIndices, std::vector<int>& textureCoordIndices, std::vector<int>& normalIndices) {
//        std::string vertexIndexStr, textureCoordIndexStr, normalIndexStr;
//        while (iss >> vertexIndexStr >> textureCoordIndexStr >> normalIndexStr) {
//            int vertexIndex, textureCoordIndex, normalIndex;
//            if (!parseIndex(vertexIndexStr, vertexIndex) || !parseIndex(textureCoordIndexStr, textureCoordIndex) || !parseIndex(normalIndexStr, normalIndex)) {
//                return false;
//            }
//            vertexIndices.push_back(vertexIndex);
//            textureCoordIndices.push_back(textureCoordIndex);
//            normalIndices.push_back(normalIndex);
//        }
//        return true;
//    }
//
//    bool parseIndex(const std::string& indexStr, int& index) {
//        std::size_t slashPos = indexStr.find('/');
//        if (slashPos == std::string::npos) {
//            return false;
//        }
//        std::string numberStr = indexStr.substr(0, slashPos);
//        try {
//            index = std::stoi(numberStr);
//        }
//        catch (std::invalid_argument&) {
//            return false;
//        }
//        catch (std::out_of_range&) {
//            return false;
//        }
//        return true;
//    }
//};

class ModelLoader {
public:
    bool isLoad(const std::string& path) {
        std::ifstream file(path);
        return file.good();
    }

    bool loadModel(const std::string& path) {
        std::ifstream file(path);
        if (!file.good()) {
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("v ") == 0) {
                float vertex[3];
                if (!parseVertices(line.substr(2), vertex)) {
                    return false;
                }
                vertices.push_back(vertex[0]);
                vertices.push_back(vertex[1]);
                vertices.push_back(vertex[2]);
            }
            else if (line.find("vt ") == 0) {
                float textureCoordinate[2];
                if (!parseTextureCoords(line.substr(3), textureCoordinate)) {
                    return false;
                }
                textureCoords.push_back(textureCoordinate[0]);
                textureCoords.push_back(textureCoordinate[1]);
            }
            else if (line.find("vn ") == 0) {
                float normal[3];
                if (!parseNormal(line.substr(3), normal)) {
                    return false;
                }
                normals.push_back(normal[0]);
                normals.push_back(normal[1]);
                normals.push_back(normal[2]);
            }
            else if (line.find("f ") == 0) {
                std::stringstream ss(line.substr(2));
                std::string s;
                while (std::getline(ss, s, ' ')) {
                    if (!s.empty()) {
                        std::stringstream ssIndex(s);
                        std::string sIndex;
                        std::vector<std::string> tokensIndex;
                        while (std::getline(ssIndex, sIndex, '/')) {
                            if (!sIndex.empty()) {
                                tokensIndex.push_back(sIndex);
                            }
                        }
                        if (tokensIndex.size() != 3) {
                            return false;
                        }
                        unsigned int indexVertex = std::stoi(tokensIndex[0]) - 1;
                        unsigned int indexTextureCoord = std::stoi(tokensIndex[1]) - 1;
                        unsigned int indexNormal = std::stoi(tokensIndex[2]) - 1;
                        indices.push_back(indexVertex);
                        /*indices.push_back(indexTextureCoord);
                        indices.push_back(indexNormal);*/
                    }
                }
            }
        }

        return true;
    }

    std::vector<float> getVertices() {
        return vertices;
    }

    std::vector<float> getTextureCoords() {
        return textureCoords;
    }

    std::vector<float> getNormals() {
        return normals;
    }

    std::vector<unsigned int> getIndices() {
        return indices;
    }


private:
    bool parseVertices(const std::string& strVertex, float* vertex) {
        std::stringstream ss(strVertex);
        std::string s;
        std::vector<std::string> tokens;
        while (std::getline(ss, s, ' ')) {
            if (!s.empty()) {
                tokens.push_back(s);
            }
        }
        if (tokens.size() != 3) {
            return false;
        }
        vertex[0] = std::stof(tokens[0]);
        vertex[1] = std::stof(tokens[1]);
        vertex[2] = std::stof(tokens[2]);
        return true;
    }

    bool parseTextureCoords(const std::string& strTextureCoordinate, float* textureCoordinate) {
        std::stringstream ss(strTextureCoordinate);
        std::string s;
        std::vector<std::string> tokens;
        while (std::getline(ss, s, ' ')) {
            if (!s.empty()) {
                tokens.push_back(s);
            }
        }
        if (tokens.size() != 2) {
            return false;
        }
        textureCoordinate[0] = std::stof(tokens[0]);
        textureCoordinate[1] = std::stof(tokens[1]);
        return true;
    }

    bool parseNormal(const std::string& strNormal, float* normal) {
        std::stringstream ss(strNormal);
        std::string s;
        std::vector<std::string> tokens;
        while (std::getline(ss, s, ' ')) {
            if (!s.empty()) {
                tokens.push_back(s);
            }
        }
        if (tokens.size() != 3) {
            return false;
        }
        normal[0] = std::stof(tokens[0]);
        normal[1] = std::stof(tokens[1]);
        normal[2] = std::stof(tokens[2]);
        return true;
    }

    std::vector<float> vertices;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
};


