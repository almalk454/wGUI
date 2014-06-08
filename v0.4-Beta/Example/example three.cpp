#include "wGUI.h"

LPTSTR szClassName = "App on wGUI";

void onButtonClick(TButton* self)
{
  MessageBoxA(0, "Was clicked button!", szClassName, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  wgui.init(hInstance, szClassName);
  TForm form1 = wgui.CreateForm("Form Caption", 500, 400);
  TButton button1("Button");
  button1.onClick = onButtonClick;
  wgui.addGUI(&button1, &form1);
  
  
  wGUI_MSGS;///(!) necessarily...
}
