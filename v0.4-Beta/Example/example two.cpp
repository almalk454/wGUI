#include "wGUI"

LPTSTR szClassName = "App on wGUI";


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  wgui.init(hInstance, szClassName);
  TForm form1 = wgui.CreateForm("Form Caption", 500, 400);
  TButton button1("Button");
  wgui.addGUI(&button1, &form1);
  
  
  wGUI_MSGS;///(!) necessarily...
}
