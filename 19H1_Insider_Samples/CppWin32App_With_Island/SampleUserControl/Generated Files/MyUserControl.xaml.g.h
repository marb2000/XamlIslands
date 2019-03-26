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

        ::winrt::Windows::UI::Xaml::Controls::TextBox Text1()
        {
            return _Text1;
        }
        void Text1(::winrt::Windows::UI::Xaml::Controls::TextBox value)
        {
            _Text1 = value;
        }

        ::winrt::Windows::UI::Xaml::Controls::Button Button1()
        {
            return _Button1;
        }
        void Button1(::winrt::Windows::UI::Xaml::Controls::Button value)
        {
            _Button1 = value;
        }

        ::winrt::Windows::UI::Xaml::Controls::Button Button2()
        {
            return _Button2;
        }
        void Button2(::winrt::Windows::UI::Xaml::Controls::Button value)
        {
            _Button2 = value;
        }

        ::winrt::Windows::UI::Xaml::Controls::Button Button3()
        {
            return _Button3;
        }
        void Button3(::winrt::Windows::UI::Xaml::Controls::Button value)
        {
            _Button3 = value;
        }

        ::winrt::SampleUserControl::InternalUserControl internalUserControl()
        {
            return _internalUserControl;
        }
        void internalUserControl(::winrt::SampleUserControl::InternalUserControl value)
        {
            _internalUserControl = value;
        }
        
    protected:
        bool _contentLoaded{false};

    private:
        struct MyUserControl_obj1_Bindings;

        ::winrt::Windows::UI::Xaml::Controls::TextBox _Text1{nullptr};
        ::winrt::Windows::UI::Xaml::Controls::Button _Button1{nullptr};
        ::winrt::Windows::UI::Xaml::Controls::Button _Button2{nullptr};
        ::winrt::Windows::UI::Xaml::Controls::Button _Button3{nullptr};
        ::winrt::SampleUserControl::InternalUserControl _internalUserControl{nullptr};
    };
}
