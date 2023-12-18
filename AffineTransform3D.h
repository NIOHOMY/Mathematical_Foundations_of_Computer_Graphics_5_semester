//#ifndef AFFINE_TRANSFORM_H
//#define AFFINE_TRANSFORM_H
//#include <math.h>
//
//glm::mat4<> Translation(double x, double y)
//{
//	double T[9] = {
//		1, 0, x,
//		0, 1, y,
//		0, 0, 1 };
//	return Matrix<>(3, 3, T);
//}
//
//glm::mat4<> Identity()
//{
//	double I[9] = {
//		1, 0, 0,
//		0, 1, 0,
//		0, 0, 1 };
//	return Matrix<>(3, 3, I);
//}
//
//glm::mat4<> Rotation(double angle)
//{
//    angle = angle * (3.14159265359 / 180.0);
//    double cosA = std::cos(angle);
//    double sinA = std::sin(angle);
//    double R[9] = {
//        cosA, -sinA, 0,
//        sinA, cosA, 0,
//        0, 0, 1,
//    };
//    return Matrix<>(3, 3, R);
//}
//
//glm::mat4<> Scaling(double scaleX, double scaleY)
//{
//    double S[9] = {
//        scaleX, 0, 0,
//        0, scaleY, 0,
//        0, 0, 1
//    };
//    return Matrix<>(3, 3, S);
//}
//
//glm::mat4<> ReflectionX()
//{
//    double RX[9] = {
//        1, 0, 0,
//        0, -1, 0,
//        0, 0, 1
//    };
//    return Matrix<>(3, 3, RX);
//}
//
//glm::mat4<> ReflectionY()
//{
//    double RY[9] = {
//        -1, 0, 0,
//        0, 1, 0,
//        0, 0, 1
//    };
//    return Matrix<>(3, 3, RY);
//}
//
//
//#endif AFFINE_TRANSFORM_H

#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include <glm/glm.hpp>

glm::mat4 Translation(double x, double y)
{
    glm::mat4 result(1.0f);
    result[3][0] = x;
    result[3][1] = y;
    return result;
}

glm::mat4 Identity()
{
    return glm::mat4(1.0f);
}

glm::mat4 Rotation(double angle)
{
    angle = glm::radians(static_cast<float>(angle));
    glm::mat4 result(1.0f);
    result[0][0] = std::cos(angle);
    result[0][1] = -std::sin(angle);
    result[1][0] = std::sin(angle);
    result[1][1] = std::cos(angle);
    return result;
}

glm::mat4 Scaling(double scaleX, double scaleY)
{
    glm::mat4 result(1.0f);
    result[0][0] = scaleX;
    result[1][1] = scaleY;
    return result;
}

glm::mat4 ReflectionX()
{
    glm::mat4 result(1.0f);
    result[1][1] = -1.0f;
    return result;
}

glm::mat4 ReflectionY()
{
    glm::mat4 result(1.0f);
    result[0][0] = -1.0f;
    return result;
}

#endif // AFFINE_TRANSFORM_H
