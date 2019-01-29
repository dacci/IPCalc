// Copyright (c) 2016 dacci.org

#include "app/application.h"

#include "ui/main_dialog.h"

CAppModule _Module;

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
                       wchar_t* /*command_line*/, int /*show_mode*/) {
  HRESULT result;

  result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
  if (FAILED(result))
    return __LINE__;

  if (!AtlInitCommonControls(0xFFFF))  // all classes
    return __LINE__;

  result = _Module.Init(nullptr, hInstance);
  if (FAILED(result))
    return __LINE__;

  {
    CMessageLoop message_loop;
    if (!_Module.AddMessageLoop(&message_loop))
      return __LINE__;

    MainDialog dialog;
    if (dialog.Create(NULL)) {
      dialog.ShowWindow(SW_SHOW);
      dialog.UpdateWindow();
    } else {
      return __LINE__;
    }

    message_loop.Run();

    _Module.RemoveMessageLoop();
  }

  _Module.Term();
  CoUninitialize();

  return 0;
}
