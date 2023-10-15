#pragma once
#include "Model2D.h"
#include <windef.h>
#include <wingdi.h>
#include <windowsx.h>

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices)
    : m_vertices(vertices), m_indices(indices), m_modelMatrix(vertices.size(), 3)
{
    // Заполнение матрицы m_modelMatrix с использованием векторов x и y
    for (int i = 0; i < m_vertices.size(); i++) {
        m_modelMatrix(i+1, 1) = m_vertices[i].x();
        m_modelMatrix(i+1, 2) = m_vertices[i].y();
        m_modelMatrix(i+1, 3) = 1.0;
    }
}


void Model2D::draw(const HDC& hdc)
{
    // Выполнить преобразования над вершинами модели
    std::vector<Vector2D> transformedVertices(m_vertices.size());
    for (int i = 0; i < m_vertices.size(); i++) {
        if (i >= m_vertices.size())// Индекс выходит за пределы вектора, обработка ошибки
            break;
        Matrix<> point(3, 1);
        point(1, 1) = m_vertices[i].x();
        point(2, 1) = m_vertices[i].y();
        point(3, 1) = 1;
        Matrix<> transformedPoint = m_modelMatrix * point;
        transformedVertices[i] = Vector2D(transformedPoint(1, 1), transformedPoint(2, 1));
    }

    // Отрисовать модель на экране
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    for (int i = 0; i < m_indices.size()-1; i++) {
        MoveToEx(hdc, transformedVertices[m_indices[i]].x(), transformedVertices[m_indices[i]].y(), nullptr);
        LineTo(hdc, transformedVertices[m_indices[i + 1]].x(), transformedVertices[m_indices[i + 1]].y());
    }
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}

