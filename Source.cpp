#include <Windows.h>
#include <windowsx.h>
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
    static Loader loader("triangle.txt"); // Путь к файлу треугольника

    static HDC hdc = NULL; // Добавьте статическую переменную hdc

    switch (msg)
    {
    case WM_CREATE:
    {
        // Установите значение hWnd при создании окна
        hdc = GetDC(hWnd);

        // Создаем 2D-модель треугольника.
        std::vector<Vector2D> vertices = loader.vertices();
        std::vector<int> indices = loader.indices();
        figures.push_back(new Model2D(vertices, indices));
        //Model2D triangle(vertices, indices);

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
    default:
        if (hWnd == NULL) { // Проверяем значение hWnd перед вызовом DefWindowProc
            OutputDebugStringA("Error: invalid HDC.\n");
        }
        else {
            return DefWindowProc(hWnd, msg, wp, lp);
        }
    }

    return 0;
}

