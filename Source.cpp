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

            /*
            // Создаем 2D-модель треугольника.
            std::vector<Vector2D> vertices = loader.vertices();
            std::vector<int> indices = loader.indices();
            figures.push_back(new Model2D(vertices, indices));
            //Model2D triangle(vertices, indices);
            */
            // Создаем 2D-модель квадрата.
            std::vector<Vector2D> vertices2 = loader2.vertices();
            std::vector<int> indices2 = loader2.indices();
            figures.push_back(new Model2D(vertices2, indices2));

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
            
            Vector2D O = model->getOXOYVector();

            switch (wp)
            {
                case 'W':
                    model->applyTransformation(Translation(0, -50));
                    break;
                case 'A':
                    model->applyTransformation(Translation(-50, 0));
            
                    break;
                case 'S':
                    model->applyTransformation(Translation(0, 50));
            
                    break;
                case 'D':
                    model->applyTransformation(Translation(50, 0));
                    break;
                case 'Z':
                {
                    model->applyTransformation(Scaling(0.5, 0.5) * Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'X':
                {   
                    model->applyTransformation(Scaling(2, 2) * Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'R':
                {
                    model->applyTransformation(ReflectionX()* Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'F':
                {
                    model->applyTransformation(ReflectionY() * Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'Q':
                {
                    model->applyTransformation(Rotation(-10)* Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'E':
                {
                    model->applyTransformation(Rotation(10)* Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
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

