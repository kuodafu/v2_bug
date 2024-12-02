#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <CommCtrl.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    HWND hWnd = CreateWindowExW(0, L"#32770", L"123", 0x16CF0000, 100, 100, 800, 600, 0, 0, 0, 0);

    const DWORD style = WS_BORDER | WS_VISIBLE | WS_CHILD |
        TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT;
    HWND hTree = CreateWindowExW(WS_EX_COMPOSITED, L"SysTreeView32", 0, 0x54B05027, 0, 0, 700, 500, hWnd, 0, 0, 0);
    TVINSERTSTRUCTW is = { 0 };
    is.item.mask = TVIF_TEXT;
    is.item.pszText = (LPWSTR)
        L"需要启用视觉样式6.0, 两个屏幕, "
        "主屏幕在右边, 缩放是150%, 分辨率2560*1440, "
        "副屏幕在左边, 缩放是100%, 分辨率1920*1080, "
        "窗口移动到左边屏幕, TreeView组件一小部分部分显示到右边屏幕, 大概50像素左右, "
        "鼠标移动到TreeView项目上, 会显示提示文本, 鼠标在左边屏幕上移动是正常显示, "
        "鼠标在右边屏幕, 移动到项目上, TreeView组件就一直触发 WM_NOTIFY消息, "
        "通知值是 NM_CUSTOMDRAW, 一直触发, 导致程序卡死, 疑似bug, "
        "版本号 22H2"
        "系统内部版本 19045.5131"
        ;
    is.item.pszText = (LPWSTR)L"--SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);";
    SendMessageW(hTree, TVM_INSERTITEM, 0, (LPARAM)&is);
    SendMessageW(hTree, TVM_INSERTITEM, 0, (LPARAM)&is);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

