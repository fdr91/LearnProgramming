﻿#include <windows.h>

/*Всё, что относится непосредственно к алгоритму находится между *BEGIN* и *END*.
Остальное -- создает и настраивает окошко для риспования */

/***********BEGIN***********/
#define W_SIZE 512
int x, y;
int h = 160;

void plot();
void a(int i);
void b(int i);
void c(int i);
void d(int i);

void a(int i){
	if (i <= 0) return;
	a(i - 1); x += h; y -= h; plot();
	b(i - 1); x += 2 * h; plot();
	d(i - 1); x += h; y += h; plot();
	a(i - 1);
}

void b(int i){
	if (i <= 0) return;
	b(i - 1); x -= h; y -= h; plot();
	c(i - 1); y -= 2 * h; plot();
	a(i - 1); x += h; y -= h; plot();
	b(i - 1);
}

void c(int i){
	if (i <= 0) return;
	c(i - 1); x -= h; y += h; plot();
	d(i - 1); x -= 2 * h; plot();
	b(i - 1); x -= h; y -= h; plot();
	c(i - 1);
}


void d(int i){
	if (i <= 0) return;
	d(i - 1); x += h; y += h; plot();
	a(i - 1); y += 2 * h; plot();
	c(i - 1); x -= h; y += h; plot();
	d(i - 1);
}

HDC hdc;


void draw(){
	h = W_SIZE / 4;
	int x0 = 2*h;
	int y0 = 3*h;
	for (int i = 1; i < 4; i++){
			x0 -= h;
			h /= 2;
			y0 += h;
			x = x0;
			y = y0;
			MoveToEx(hdc, x, y, 0);
			a(i); x += h; y -= h; plot();
			b(i); x -= h; y -= h; plot();
			c(i); x -= h; y += h; plot();
			d(i); x += h; y += h; plot();
	}

}

void plot(){
	LineTo(hdc, x, y);
}
/************END*************/

PAINTSTRUCT ps;
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
wchar_t szClassName[] = L"Krivaia Gil'berta";

int windowFacility(WNDCLASSEX &wincl, HINSTANCE &hThisInstance){

	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof (WNDCLASSEX);

	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = CreateSolidBrush(RGB(140, 140, 140));

	if (!RegisterClassEx(&wincl))
		return 0;
}


int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nFunsterStil)

{
	HWND hwnd;
	MSG messages;
	WNDCLASSEX wincl;
	windowFacility(wincl, hThisInstance);
	hwnd = CreateWindowEx(
		0,
		szClassName,
		L"Krivaia Gil'berta",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		W_SIZE + 50,
		W_SIZE + 50,
		HWND_DESKTOP,
		NULL,
		hThisInstance,
		NULL
		);
	ShowWindow(hwnd, nFunsterStil);
	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);
		draw();
		ValidateRect(hwnd, NULL);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

