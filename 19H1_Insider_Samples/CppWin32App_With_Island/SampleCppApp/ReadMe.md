# Sample Win32 app

This is a normal Win32 Windows application with an entry point in wWinMain:
```
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    winrt::MyApp::App app;


}
```
