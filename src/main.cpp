#include <iostream>

#include "windows.h"

const TCHAR* AppName = TEXT("WindowApp");

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, INT icmdShow)
{
    MSG msg;
    HWND hwnd;
    WNDCLASSEX wcex = {};

    wcex.hInstance = hinstance;
    wcex.lpszClassName = AppName;
    wcex.lpfnWndProc = MsgProc;

    if(!RegisterClassEx(&wcex))
    {
        std::cout << "Register window class Failed\n";
    }

    hwnd = CreateWindow(AppName, AppName, WS_OVERLAPPEDWINDOW, 100, 100, 640, 480, NULL, NULL, hinstance, NULL);
    ShowWindow(hwnd, icmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&msg, 0, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

