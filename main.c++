#include <Windows.h>
#include <ShlObj.h>
#include <iostream>
#include <string>

const std::wstring ROOT_FOLDER = L"C:\\root"; // Path to "root" folder
HWND nextClipboardViewer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to check if file path starts with ROOT_FOLDER
bool IsInsideRootFolder(const std::wstring& path) {
    return path.compare(0, ROOT_FOLDER.size(), ROOT_FOLDER) == 0;
}

// Function to clear clipboard if files are outside "root" folder
void RestrictClipboard() {
    std::cout << "RestrictClipboard() called\n";
    if (OpenClipboard(nullptr)) {
        HANDLE hData = GetClipboardData(CF_HDROP);
        if (hData) {
            HDROP hDrop = static_cast<HDROP>(hData);
            UINT fileCount = DragQueryFileW(hDrop, 0xFFFFFFFF, nullptr, 0);
            
            for (UINT i = 0; i < fileCount; ++i) {
                wchar_t filePath[MAX_PATH];
                DragQueryFileW(hDrop, i, filePath, MAX_PATH);

                std::wcout << L"Checking file: " << filePath << std::endl;

                // Check if any file path is outside ROOT_FOLDER
                if (!IsInsideRootFolder(filePath)) {
                    EmptyClipboard(); // Restrict the operation
                    MessageBoxW(nullptr, L"Copy-paste outside the root folder is restricted.", L"Restriction", MB_ICONWARNING);
                    break;
                }
            }
            DragFinish(hDrop);
        } else {
            std::cout << "No files found in clipboard\n";
        }
        CloseClipboard();
    } else {
        std::cout << "Failed to open clipboard\n";
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    // Register window class
    const wchar_t CLASS_NAME[] = L"ClipboardRestrictionWindow";
    
    WNDCLASSW wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Clipboard Restriction",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    nextClipboardViewer = SetClipboardViewer(hwnd);

    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Main Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        nextClipboardViewer = SetClipboardViewer(hwnd);
        std::cout << "WM_CREATE received - Clipboard viewer chain started\n";
        break;

    case WM_DRAWCLIPBOARD:
        std::cout << "WM_DRAWCLIPBOARD received - Clipboard updated\n";
        RestrictClipboard(); // Check clipboard content whenever it changes
        SendMessage(nextClipboardViewer, uMsg, wParam, lParam);
        break;

    case WM_CHANGECBCHAIN:
        std::cout << "WM_CHANGECBCHAIN received - Clipboard viewer chain changed\n";
        if ((HWND)wParam == nextClipboardViewer) {
            nextClipboardViewer = (HWND)lParam;
        } else if (nextClipboardViewer) {
            SendMessage(nextClipboardViewer, uMsg, wParam, lParam);
        }
        break;

    case WM_DESTROY:
        std::cout << "WM_DESTROY received - Cleaning up\n";
        ChangeClipboardChain(hwnd, nextClipboardViewer);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
