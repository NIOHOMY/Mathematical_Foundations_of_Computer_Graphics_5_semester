#include <Windows.h>
#include <windowsx.h>
#include "AffineTransform.h"
#include "Loader.h"
#include "Render2D.h"

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

Render2D render;
std::vector<Model2D*> figures;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClassW(&mainWindow))
		return -1;

    CreateWindow(L"MainWndClass", L"MainWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, hInstance, NULL);

	MSG message = { 0 };
    while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HDC hdc = NULL; // Добавьте статическую переменную hdc

    switch (msg)
    {
        case WM_CREATE:
        {
            static Loader loader("triangle.txt"); // Путь к файлу треугольника
            static Loader loader2("square.txt"); // Путь к файлу треугольника
            // Установите значение hWnd при создании окна
            hdc = GetDC(hWnd);

            // Создаем 2D-модель треугольника.
            std::vector<Vector2D> vertices = loader.vertices();
            std::vector<int> indices = loader.indices();
            figures.push_back(new Model2D(vertices, indices));
            //Model2D triangle(vertices, indices);
            // Создаем 2D-модель квадрата.
            /*
            std::vector<Vector2D> vertices2 = loader2.vertices();
            std::vector<int> indices2 = loader2.indices();
            figures.push_back(new Model2D(vertices2, indices2));
            */

            // Инициализируем экземпляр класса Render2D и добавляем треугольник в список объектов.
            for (Model2D* _model : figures)
            {
                render.addObject(_model);
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            render.draw(hdc);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_KEYDOWN:
        {
            Model2D* model = render.getObject(0);
            
            Vector2D O = model->goToOXOY();
            Matrix<> ToO = Translation(O.x(), O.y());
            Matrix<> BackO = Translation(-O.x(), -O.y());
            // Создаем матрицы преобразования
            Matrix<> up = Translation(0,-50);
            Matrix<> down = Translation(0,50);
            Matrix<> left = Translation(-50,0);
            Matrix<> right = Translation(50,0);

            Matrix<> minimise = Scaling(0.5,0.5);
            Matrix<> maximise = Scaling(2,2);

            Matrix<> reflectionX = ReflectionX();
            Matrix<> reflectionY = ReflectionY();

            Matrix<> leftRotation = Rotation(10);
            Matrix<> rightRotation = Rotation(-10);

            switch (wp)
            {
                case 'W':
                    model->applyTransformation(up);
                    break;
                case 'A':
                    model->applyTransformation(left);
            
                    break;
                case 'S':
                    model->applyTransformation(down);
            
                    break;
                case 'D':
                    model->applyTransformation(right);
                    break;
                case 'Z':
                {
                    model->applyTransformation(ToO);
                    model->applyTransformation(minimise);
                    model->applyTransformation(BackO);
                    break;
                }
                case 'X':
                {
                    model->applyTransformation(ToO);
                    model->applyTransformation(maximise);
                    model->applyTransformation(BackO);
                    break;
                }
                case 'R':
                {
                    model->applyTransformation(ToO);
                    model->applyTransformation(reflectionX);
                    model->applyTransformation(BackO);
                    break;
                }
                case 'F':
                {
                    model->applyTransformation(ToO);
                    model->applyTransformation(reflectionY);
                    model->applyTransformation(BackO);
                    break;
                }
                case 'Q':
                {
                    model->applyTransformation(ToO);
                    model->applyTransformation(leftRotation);
                    model->applyTransformation(BackO);
                    break;
                }
                case 'E':
                {
                    model->applyTransformation(ToO);
                    model->applyTransformation(rightRotation);
                    model->applyTransformation(BackO);
                    break;
                }
                break;
            }

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        default:
        {
            if (hWnd == NULL) { // Проверяем значение hWnd перед вызовом DefWindowProc
                OutputDebugStringA("Error: invalid HDC.\n");
            }
            else {
                return DefWindowProc(hWnd, msg, wp, lp);
            }
        }
    }

    return 0;
}

