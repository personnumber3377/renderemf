// RenderEMF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <gdiplus.h>
#include <iostream>

using namespace Gdiplus;



/*
int main() {
    // Initialize GDI+
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiStartupInput, NULL);

    // Load EMF file
    const WCHAR* emfFilePath = L"image.emf";
    Image image(emfFilePath);

    // Create a device context (HDC) to render the EMF image
    HDC hdc = GetDC(NULL);  // Use screen's DC or create a window context
    Graphics graphics(hdc);

    // Draw the EMF file on the screen at (0,0)
    graphics.DrawImage(&image, 0, 0);

    // Release resources
    ReleaseDC(NULL, hdc);
    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 0;
}
*/

















/*

#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

// Global variables for the GDI+ token and the window handle
ULONG_PTR gdiplusToken;
HWND hwnd;

// Window procedure for handling messages
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Load the EMF file
        // const WCHAR* emfFilePath = L"C:\\Users\\elsku\\source\\repos\\RenderEMF\\x64\\Debug\\image.emf";
        const WCHAR* emfFilePath = L"C:\\Users\\elsku\\image.emf";
        Image image(emfFilePath);
        if (image.GetLastStatus() != Ok) {
            printf("Failed to load EMF file.\n");
            return -1;
        }
        // Get the dimensions of the window
        RECT rect;
        GetClientRect(hWnd, &rect);

        // Create a GDI+ graphics object
        Graphics graphics(hdc);

        // Calculate the center position
        int imgWidth = image.GetWidth();
        int imgHeight = image.GetHeight();
        int x = (rect.right - imgWidth) / 2;
        int y = (rect.bottom - imgHeight) / 2;

        // Draw the image centered
        printf("%s\n", "Drawing the image");
        graphics.DrawImage(&image, x, y);

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_TIMER: {
        // Destroy the window after the timer expires
        KillTimer(hWnd, 1);  // Stop the timer
        DestroyWindow(hWnd); // Close the window
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main() {
    // Initialize GDI+
    GdiplusStartupInput gdiStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiStartupInput, NULL);

    // Register the window class
    const wchar_t CLASS_NAME[] = L"FullscreenWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Get the screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a borderless fullscreen window
    hwnd = CreateWindowEx(
        WS_EX_TOPMOST,               // Always on top
        CLASS_NAME,                  // Window class
        L"Render EMF",                // Window title
        WS_POPUP,                    // No borders or title bar
        0, 0,                        // Position (top-left corner)
        screenWidth, screenHeight,   // Fullscreen dimensions
        NULL, NULL, NULL, NULL
    );

    if (!hwnd) {
        printf("Failed to create window.\n");
        return -1;
    }

    // Show the window
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    SetTimer(hwnd, 1, 400, NULL);
    // Message loop
    MSG msg = {};
    
    unsigned int i = 0;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        i++; // Increment
        if (i == 100) {
            break;
        }
    }
    
    printf("%s\n", "Ending the stuff");
    // Cleanup GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}








*/








#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>
#include <iostream>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;
using namespace std;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static Image* currentImage = nullptr;

    switch (uMsg) {
    
    case WM_USER: {  // Custom message to update the image
        currentImage = (Image*)lParam;  // Assign the Image pointer passed via LPARAM
        InvalidateRect(hWnd, NULL, TRUE);  // Force the window to redraw
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        printf("Oofstuff...\n");
        if (currentImage && currentImage->GetLastStatus() == Ok) {
            RECT rect;
            GetClientRect(hWnd, &rect);

            // Center the image
            Graphics graphics(hdc);
            int x = (rect.right - currentImage->GetWidth()) / 2;
            int y = (rect.bottom - currentImage->GetHeight()) / 2;
            printf("Drawing an image...\n");
            graphics.DrawImage(currentImage, x, y);
        }

        EndPaint(hWnd, &ps);
        return 0;
    }
    
    
    /*
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Load the EMF file
        // const WCHAR* emfFilePath = L"C:\\Users\\elsku\\source\\repos\\RenderEMF\\x64\\Debug\\image.emf";
        const WCHAR* emfFilePath = L"C:\\Users\\elsku\\image.emf";
        Image image(emfFilePath);
        if (image.GetLastStatus() != Ok) {
            printf("Failed to load EMF file.\n");
            return -1;
        }
        // Get the dimensions of the window
        RECT rect;
        GetClientRect(hWnd, &rect);

        // Create a GDI+ graphics object
        Graphics graphics(hdc);

        // Calculate the center position
        int imgWidth = image.GetWidth();
        int imgHeight = image.GetHeight();
        int x = (rect.right - imgWidth) / 2;
        int y = (rect.bottom - imgHeight) / 2;

        // Draw the image centered
        printf("%s\n", "Drawing the image");
        graphics.DrawImage(&image, x, y);

        EndPaint(hWnd, &ps);
        return 0;
    }
    */

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Function to list all files in a directory
vector<wstring> GetFilesInDirectory(const wstring& directoryPath) {
    vector<wstring> files;
    WIN32_FIND_DATA findData;

    wstring searchPath = directoryPath + L"\\*";
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        wcerr << L"Failed to open directory: " << directoryPath << endl;
        return files;
    }

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            files.push_back(directoryPath + L"\\" + findData.cFileName);
        }
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
    return files;
}

int main() {
    // Initialize GDI+
    GdiplusStartupInput gdiStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiStartupInput, NULL);

    // Register the window class
    const wchar_t CLASS_NAME[] = L"FullscreenWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Get the screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    printf("screenWidth: %d\n", screenWidth);
    printf("screenHeight: %d\n", screenHeight);
    screenWidth = 300;
    screenHeight = 300;
    // Directory containing EMF files
    wstring directoryPath = L"C:\\Users\\elsku\\outputs4\\queue";

    // Get all files in the directory
    vector<wstring> files = GetFilesInDirectory(directoryPath);
    if (files.empty()) {
        wcerr << L"No files found in directory: " << directoryPath << endl;
        GdiplusShutdown(gdiplusToken);
        return -1;
    }

    for (const auto& filePath : files) {
        // Create the window
        HWND hwnd = CreateWindowEx(
            WS_EX_TOPMOST,
            CLASS_NAME,
            L"Render EMF",
            WS_POPUP,
            0, 0,
            screenWidth, screenHeight,
            NULL, NULL, NULL, NULL
        );

        if (!hwnd) {
            wcerr << L"Failed to create window for file: " << filePath << endl;
            continue;
        }

        // Load the current image
        Image* image = new Image(filePath.c_str());
        if (image->GetLastStatus() != Ok) {
            wcerr << L"Failed to load image: " << filePath << endl;
            delete image;
            continue;
        }
        SendMessage(hwnd, WM_USER, 0, (LPARAM)image); // Send the image stuff.

        wcerr << L"Loaded this image: " << filePath << endl;
        // printf("Loaded this file: %s\n", filePath.c_str());
        // Pass the image to the window procedure
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)&image);

        // Show the window
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        // Render the image for 0.2 seconds
        // Sleep(100);

        // Close the window
        DestroyWindow(hwnd);
    }

    // Cleanup GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}


















// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
