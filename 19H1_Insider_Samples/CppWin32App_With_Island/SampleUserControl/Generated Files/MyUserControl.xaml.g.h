﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#pragma once


namespace winrt::SampleUserControl::implementation
{
    using IInspectable = ::winrt::Windows::Foundation::IInspectable;

    template <typename D, typename ... I>
    struct MyUserControlT : public ::winrt::SampleUserControl::implementation::MyUserControl_base<D,
        ::winrt::Windows::UI::Xaml::Markup::IComponentConnector,
        ::winrt::Windows::UI::Xaml::Markup::IComponentConnector2,
        I...>
    {
        using base_type = typename MyUserControlT::base_type;
        using base_type::base_type;
        using class_type = typename MyUserControlT::class_type;

        void InitializeComponent();
        void Connect(int32_t connectionId, IInspectable const& target);
        ::winrt::Windows::UI::Xaml::Markup::IComponentConnector GetBindingConnector(int32_t connectionId, IInspectable const& target);
        void UnloadObject(::winrt::Windows::UI::Xaml::DependencyObject const& dependencyObject);
        void DisconnectUnloadedObject(int32_t connectionId);

        ::winrt::Windows::UI::Xaml::Controls::Button Button()
        {
            return _Button;
        }
        void Button(::winrt::Windows::UI::Xaml::Controls::Button value)
        {
            _Button = value;
        }
        
    protected:
        bool _contentLoaded{false};

    private:
        struct MyUserControl_obj1_Bindings;

        ::winrt::Windows::UI::Xaml::Controls::Button _Button{nullptr};
    };
}

