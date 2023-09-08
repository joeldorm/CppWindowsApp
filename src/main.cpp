#include <iostream>

#include "windows.h"

const TCHAR* AppName = TEXT("WindowApp");

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, INT icmdShow)
{
    MSG msg;
    HWND hwnd;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = MsgProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hinstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = AppName;

    if(!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program require Window NT!"), AppName, MB_ICONERROR);
        std::cout << "Register window class Failed\n";
        return 0;
    }

    hwnd = CreateWindow(AppName, AppName, WS_OVERLAPPEDWINDOW, 100, 100, 640, 480, NULL, NULL, hinstance, NULL);
    ShowWindow(hwnd, icmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    const TCHAR* myText = TEXT("Hello, World!");
    static int cxChar, cxCaps, cyChar;
    HDC hdc;

    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(msg)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        ReleaseDC(hwnd, hdc);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 0, cyChar + 20, myText, sizeof(TCHAR*));
        SetTextAlign(hdc, TA_LEFT | TA_TOP);

        TextOut(hdc, 22 * cxCaps + 40, cyChar + 80, myText, sizeof(myText));
        SetTextAlign(hdc, TA_RIGHT | TA_BOTTOM);

        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

