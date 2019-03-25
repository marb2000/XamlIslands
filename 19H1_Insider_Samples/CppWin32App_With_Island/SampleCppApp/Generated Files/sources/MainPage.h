#pragma once

#include "MainPage.g.h"

namespace winrt::SampleCppApp::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::SampleCppApp::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
