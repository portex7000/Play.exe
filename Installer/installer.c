#include <windows.h>
#include <stdio.h>

// Forward declarations
LRESULT CALLBACK DialogProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void ExtractAndCopyExecutable();

// Resource IDs
#define ID_INSTALL 1
#define ID_EXIT 2

// Main entry point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Create a dialog box
    HWND hwnd = CreateDialogParam(hInstance, MAKEINTRESOURCE(101), 0, DialogProc, 0);
    ShowWindow(hwnd, nCmdShow);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!IsDialogMessage(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

// Dialog procedure to handle button clicks
LRESULT CALLBACK DialogProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_INSTALL:
                    ExtractAndCopyExecutable();
                    MessageBox(hwnd, "Installation completed successfully.", "Success", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_EXIT:
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

// Function to extract and copy the embedded executable
void ExtractAndCopyExecutable() {
    // Locate the embedded resource
    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(102), RT_RCDATA);
    if (hResource == NULL) {
        MessageBox(NULL, "Failed to find resource.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    HGLOBAL hLoadedResource = LoadResource(NULL, hResource);
    if (hLoadedResource == NULL) {
        MessageBox(NULL, "Failed to load resource.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Get the size and pointer to the resource data
    DWORD resourceSize = SizeofResource(NULL, hResource);
    void* resourceData = LockResource(hLoadedResource);
    if (resourceData == NULL) {
        MessageBox(NULL, "Failed to lock resource.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Write the resource to C:\Windows\play.exe
    const char* outputPath = "C:\\Windows\\play.exe";
    FILE* outputFile = fopen(outputPath, "wb");
    if (outputFile == NULL) {
        MessageBox(NULL, "Failed to write file to C:\\Windows.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    fwrite(resourceData, 1, resourceSize, outputFile);
    fclose(outputFile);
}

// Resource file (to embed play.exe)
// Add this to a .rc file and include it in the project:
/*
101 DIALOGEX DISCARDABLE  0, 0, 150, 75
STYLE DS_CENTER | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Installer"
FONT 8, "MS Sans Serif"
BEGIN
    DEFPUSHBUTTON   "Install", ID_INSTALL, 10, 50, 50, 14
    PUSHBUTTON      "Exit", ID_EXIT, 90, 50, 50, 14
END

102 RCDATA DISCARDABLE "play.exe"
*/
