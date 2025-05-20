#include <windows.h>
#include <tchar.h>
#include <vector>
#include <stack>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;
WCHAR szTitle[] = L"L1";
WCHAR szWindowClass[] = L"WindowClass";

const int WIDTH = 764;
const int HEIGHT = 616;

enum FigureType {
	LineType,
	RectType,
	EllipseType
};

struct Figure {
	POINTFLOAT pos[2];
	FigureType type;
};

struct Button {
	POINT pos[2];
	const wchar_t* text;
	void(*func)();
};

FigureType choosenFigure = LineType;

std::vector<Figure> figures;
std::vector<Button> buttons;
std::stack<std::pair<POINTFLOAT, POINTFLOAT>> zooms;

POINT positions[2] = { 0, 0 };
POINTFLOAT gwin[2] = { {0, 0}, {1, 1} };
POINTFLOAT viewport[2] = { {0, 128}, {440, 568} };

bool isDrawing = false;
bool isZoomify = false;
float sx = 1;
float sy = 1;

HBRUSH brush;
HPEN pen;

POINTFLOAT ndc_to_dc(POINTFLOAT coords) {
	float sx = (float)(viewport[1].x - viewport[0].x) / (gwin[1].x - gwin[0].x);
	float sy = (float)(viewport[1].y - viewport[0].y) / (gwin[1].y - gwin[0].y);

	float x_v = viewport[0].x + (float)((coords.x - gwin[0].x) * sx);
	float y_v = viewport[0].y + (float)((coords.y - gwin[0].y) * sy);

	return { x_v, y_v };
}

POINTFLOAT dc_to_ndc(POINT coords) {
	float x_v = gwin[0].x + (coords.x - viewport[0].x) * (gwin[1].x - gwin[0].x) / (viewport[1].x - viewport[0].x);
	float y_v = gwin[0].y + (coords.y - viewport[0].y) * (gwin[1].y - gwin[0].y) / (viewport[1].y - viewport[0].y);

	return { x_v, y_v };
}

void draw_figure(HDC hdc, Figure figure) {
	POINTFLOAT vfp[2] = { ndc_to_dc(figure.pos[0]), ndc_to_dc(figure.pos[1]) };
	switch (figure.type)
	{
	case LineType:
		MoveToEx(hdc, vfp[0].x, vfp[0].y, NULL);
		LineTo(hdc, vfp[1].x, vfp[1].y);
		break;
	case RectType:
	{
		HBRUSH _brush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
		HGDIOBJ st = SelectObject(hdc, _brush);
		Rectangle(hdc, vfp[0].x, vfp[0].y, vfp[1].x, vfp[1].y);
		SelectObject(hdc, st);
	}
	break;
	case EllipseType:
		Ellipse(hdc, vfp[0].x, vfp[0].y, vfp[1].x, vfp[1].y);
		break;
	}
}

void drawing_figures(HDC hdc) {
	for (size_t i = 0; i < figures.size(); i++)
	{
		draw_figure(hdc, figures.at(i));
	}
}

void create_figure() {
	Figure fig = {};
	fig.type = choosenFigure;
	fig.pos[0] = dc_to_ndc(positions[0]);
	fig.pos[1] = dc_to_ndc(positions[1]);
	figures.push_back(fig);
}

int get_quadYcoords(POINT pos[2]) {
	int y = pos[1].x - pos[0].x;
	if (y < 0) y *= -1;
	return pos[1].y >= pos[0].y ? pos[0].y + y : pos[0].y - y;
}

void zoomify() {
	zooms.push({ gwin[0], gwin[1] });
	POINT pos1 = positions[0];
	POINT pos2 = { positions[1].x, get_quadYcoords(positions) };
	POINT minpos = { min(pos1.x, pos2.x), min(pos1.y, pos2.y) };
	POINT maxpos = { max(pos1.x, pos2.x), max(pos1.y, pos2.y) };
	gwin[0] = dc_to_ndc(minpos);
	gwin[1] = dc_to_ndc(maxpos);
}

void undo_zoomify() {
	if (zooms.empty()) return;
	std::pair<POINTFLOAT, POINTFLOAT> zoom = zooms.top();
	zooms.pop();
	gwin[0] = zoom.first;
	gwin[1] = zoom.second;
	InvalidateRect(GetActiveWindow(), NULL, TRUE);
}

bool point_in_rect(POINT* p, RECT* r) {
	return p->x >= r->left && p->x <= r->right && p->y >= r->top && p->y <= r->bottom;
}

bool handle_buttons() {
	for (size_t i = 0; i < buttons.size(); i++) {
		Button* btn = &buttons.at(i);
		RECT rect = { btn->pos[0].x, btn->pos[0].y, btn->pos[1].x, btn->pos[1].y };
		if (point_in_rect(&positions[0], &rect)) {
			btn->func();
			InvalidateRect(GetActiveWindow(), NULL, TRUE);
			return true;
		}
	}
	return false;
}

void add_button(POINT pos[2], const wchar_t* text, void(*func)()) {
	Button btn = {};
	btn.pos[0] = pos[0];
	btn.pos[1] = pos[1];
	btn.text = text;
	btn.func = func;
	buttons.push_back(btn);
}

void drawing_buttons(HDC hdc) {
	for (size_t i = 0; i < buttons.size(); i++)
	{
		Button* btn = &buttons.at(i);
		Rectangle(hdc, btn->pos[0].x, btn->pos[0].y, btn->pos[1].x, btn->pos[1].y);
		TextOut(hdc, btn->pos[0].x + 10, btn->pos[0].y + 10, btn->text, wcslen(btn->text));
	}
}

void drawing_controls(HDC hdc) {
	drawing_buttons(hdc);
	const wchar_t* figureTypeText = L"NONETYPE";
	switch (choosenFigure)
	{
	case LineType:
		figureTypeText = L"Line";
		break;
	case RectType:
		figureTypeText = L"Rectangle";
		break;
	case EllipseType:
		figureTypeText = L"Ellipse";
		break;
	}
	TextOut(hdc, 462, 22, L"Selected figure: ", 18);
	TextOut(hdc, 564, 22, figureTypeText, wcslen(figureTypeText));
}

void create_buttons() {
	POINT pos1[2] = { {10, 10}, {100, 50} };
	add_button(pos1, L"Line", []() { choosenFigure = LineType; });
	POINT pos2[2] = { {110, 10}, {210, 50} };
	add_button(pos2, L"Rectangle", []() { choosenFigure = RectType; });
	POINT pos3[2] = { {220, 10}, {320, 50} };
	add_button(pos3, L"Ellipse", []() { choosenFigure = EllipseType; });
	POINT pos4[2] = { {330, 10}, {430, 50} };
	add_button(pos4, L"Undo zoom", undo_zoomify);
}

bool drawing_borders() {
	RECT rect = { viewport[0].x, viewport[0].y, viewport[1].x,viewport[1].y };
	return point_in_rect(&positions[0], &rect);
}

void client_draw(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hWnd, &ps);

	drawing_controls(hdc);

	IntersectClipRect(hdc, viewport[0].x, viewport[0].y, viewport[1].x, viewport[1].y);
	HGDIOBJ st = SelectObject(hdc, pen);
	drawing_figures(hdc);
	SelectObject(hdc, st);
	const RECT vprect = { viewport[0].x, viewport[0].y, viewport[1].x, viewport[1].y };
	FrameRect(hdc, &vprect, brush);
	IntersectClipRect(hdc, 0, 0, WIDTH, HEIGHT);

	EndPaint(hWnd, &ps);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WIDTH, HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc = GetDC(hWnd);
	switch (message)
	{
	case WM_CREATE:
		brush = CreateSolidBrush(RGB(200, 0, 50));
		pen = CreatePen(PS_SOLID, 3, RGB(100, 0, 25));
		create_buttons();
		break;
	case WM_PAINT:
		client_draw(hWnd);
		break;
	case WM_RBUTTONDOWN:
		positions[0].x = LOWORD(lParam);
		positions[0].y = HIWORD(lParam);
		positions[1].x = LOWORD(lParam);
		positions[1].y = HIWORD(lParam);
		if (!drawing_borders()) break;

		isZoomify = true;
		SetROP2(hdc, R2_NOTXORPEN);
		break;
	case WM_RBUTTONUP:
		isZoomify = false;
		SetROP2(hdc, R2_COPYPEN);
		zoomify();
		positions[1].x = LOWORD(lParam);
		positions[1].y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		if (isDrawing) {
			SelectObject(hdc, pen);
			IntersectClipRect(hdc, viewport[0].x, viewport[0].y, viewport[1].x, viewport[1].y);
			MoveToEx(hdc, positions[0].x, positions[0].y, NULL);
			LineTo(hdc, positions[1].x, positions[1].y);

			positions[1].x = LOWORD(lParam);
			positions[1].y = HIWORD(lParam);

			MoveToEx(hdc, positions[0].x, positions[0].y, NULL);
			LineTo(hdc, positions[1].x, positions[1].y);
			IntersectClipRect(hdc, 0, 0, WIDTH, HEIGHT);
		}
		else if (isZoomify) {
			IntersectClipRect(hdc, viewport[0].x, viewport[0].y, viewport[1].x, viewport[1].y);
			Rectangle(hdc, positions[0].x, positions[0].y, positions[1].x, get_quadYcoords(positions));

			positions[1].x = LOWORD(lParam);
			positions[1].y = HIWORD(lParam);

			Rectangle(hdc, positions[0].x, positions[0].y, positions[1].x, get_quadYcoords(positions));
			IntersectClipRect(hdc, 0, 0, WIDTH, HEIGHT);
		}
		break;
	case WM_LBUTTONDOWN:
		positions[0].x = LOWORD(lParam);
		positions[0].y = HIWORD(lParam);
		positions[1].x = LOWORD(lParam);
		positions[1].y = HIWORD(lParam);
		if (handle_buttons()) break;
		if (isZoomify) break;
		if (!drawing_borders()) break;

		SelectObject(hdc, pen);
		IntersectClipRect(hdc, viewport[0].x, viewport[0].y, viewport[1].x, viewport[1].y);
		MoveToEx(hdc, positions[0].x, positions[0].y, NULL);
		LineTo(hdc, positions[1].x, positions[1].y);
		IntersectClipRect(hdc, 0, 0, WIDTH, HEIGHT);

		SetROP2(hdc, R2_NOTXORPEN);
		isDrawing = true;
		break;
	case WM_LBUTTONUP:
		if (isDrawing) {
			
			isDrawing = false;

			IntersectClipRect(hdc, viewport[0].x, viewport[0].y, viewport[1].x, viewport[1].y);
			MoveToEx(hdc, positions[0].x, positions[0].y, NULL);
			LineTo(hdc, positions[1].x, positions[1].y);

			positions[1].x = LOWORD(lParam);
			positions[1].y = HIWORD(lParam);

			IntersectClipRect(hdc, 0, 0, WIDTH, HEIGHT);

			SetROP2(hdc, R2_COPYPEN);

			create_figure();
			InvalidateRect(hWnd, NULL, TRUE);

		}
		break;
	case WM_DESTROY:
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}