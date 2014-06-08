#include "wGUI.h"

LPTSTR szClassName = "App on wGUI";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  wgui.init(hInstance, szClassName);
  TForm form1 = wgui.CreateForm("Form Caption", 500, 400);
  form1.Show();
  
  wGUI_MSGS;///(!) necessarily...
}
