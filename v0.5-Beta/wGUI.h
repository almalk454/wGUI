#ifndef WGUI_H
    #define WGUI_H

#ifndef _WINDOWS_H
    #include <windows.h>
#endif

#define extends : public

#define wGUI_MSGS MSG msg;\
while( GetMessage(&msg, NULL, 0, 0) )\
    {\
        TranslateMessage(&msg);\
        DispatchMessage(&msg);\
    }
#include "T.h"



LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
void wMessage(LPTSTR, LPTSTR);

class wGUI
{
protected:
    WNDCLASSEX wnd;



    TEdit* aTEdits[256];
    TListBox* aTListBoxs[256];

public:
    HINSTANCE hI;
    LPTSTR __class__;
    TButton* aTbuttons[ ];
    void init( HINSTANCE hIn, LPTSTR className, HICON hIcon = LoadIcon(NULL, IDI_APPLICATION),
         HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW) )
         {
            wnd.hInstance = hIn;
            wnd.lpszClassName = className;
            wnd.lpfnWndProc = wndProc;
            wnd.style = CS_HREDRAW | CS_VREDRAW;
            wnd.cbSize = sizeof (WNDCLASSEX);


            wnd.hIcon = wnd.hIconSm = hIcon;
            wnd.hCursor = hCursor;
            wnd.lpszMenuName = NULL;
            wnd.cbClsExtra = 0;
            wnd.cbWndExtra = 0;
            wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;

            if( !RegisterClassEx(&wnd) )
            {
                char buff [] = "Error create of class ";
                MessageBox(NULL, strcat(buff, __class__), className, NULL);
                return;
            }
            hI = hIn;
            __class__ = className;
         }
    /*TForm CreateForm( LPTSTR caption, int w, int h, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT)
    {
        TForm Form();
        Form.size.h = h;
        Form.size.w = w;
        Form.size.x = x;
        Form.size.y = y;
        Form.__caption__ = caption;

        Form.hwnd = CreateWindowEx(
                                   0,
                                   __class__,
                                   caption,
                                   WS_OVERLAPPEDWINDOW,
                                   x, y,
                                   w, h,
                                   HWND_DESKTOP,
                                   NULL,
                                   hI,
                                   NULL
                                   );
        return Form;
    }*/

    void addGUI(TButton* button, TForm* Form);
    void addGUI(TEdit* edit, TForm* Form);
    void addGUI(TLabel* label, TForm* Form);
    void addGUI(TListBox* lb, TForm* Form);


    void EventListener( WPARAM wP, LPARAM lP )
    {
        switch( HIWORD( wP ) )
        {
            case BN_CLICKED:
                    if( aTbuttons[ LOWORD( wP ) ]->onClick == NULL )
                        return;
                       aTbuttons[ LOWORD( wP ) ]->onClick( aTbuttons[ LOWORD( wP ) ] );
            break;
            case EN_CHANGE:
                    if( aTEdits[ LOWORD( wP ) ] ->onChange == NULL )
                        return;
                        aTEdits[ LOWORD( wP ) ]->onChange( aTEdits[ LOWORD( wP ) ], aTEdits[ LOWORD( wP ) ]->Text() );
            break;
            /*case BN_DBLCLK:
                wMessage("", "");
                if( aTbuttons[ LOWORD( wP ) ]->onDblClick == NULL )
                        return;
                        aTbuttons[ LOWORD( wP ) ]->onDblClick( aTbuttons[ LOWORD( wP ) ] );
            break;*/
            case EN_SETFOCUS:
                     if( aTEdits[ LOWORD( wP ) ] ->onFocus == NULL )
                        return;
                        aTEdits[ LOWORD( wP ) ]->onFocus( aTEdits[ LOWORD( wP ) ] );
            break;
        }
    }
};
wGUI wgui;

TForm::TForm(LPTSTR caption, UINT w, UINT h, int x, int y)
{
    this->hwnd = CreateWindowEx(
                                   0,
                                   wgui.__class__,
                                   caption,
                                   WS_OVERLAPPEDWINDOW,
                                   0, 0,
                                   w, h,
                                   HWND_DESKTOP,
                                   NULL,
                                   wgui.hI,
                                   NULL
                                   );
}

void wGUI::addGUI(TButton* button, TForm* Form){
    int temp = WS_CHILD | WS_VISIBLE;
    if( button->__classname__ == "checkbox" )
        temp += BS_AUTOCHECKBOX;
    button->hwnd = CreateWindow(
                                    "button",
                                    button->__caption__,
                                    temp,
                                    button->size.x, button->size.y,
                                    button->size.w, button->size.h,
                                    Form->hwnd,
                                    (HMENU)button->id,
                                    hI,
                                    NULL
                                 );
    aTbuttons[ button->id ] = button;
}
void wGUI::addGUI(TEdit* edit, TForm* Form){
    int temp = WS_CHILD | WS_VISIBLE | WS_BORDER;
    if( edit->__classname__ == "memo" ){
        temp += ES_AUTOHSCROLL | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL;
    }
    edit->hwnd = CreateWindow(
                                    "edit",
                                    edit->__caption__,
                                     temp,
                                    edit->size.x, edit->size.y,
                                    edit->size.w, edit->size.h,
                                    Form->hwnd,
                                    (HMENU)edit->id,
                                    hI,
                                    NULL
                                 );
    aTEdits[ edit->id ] = edit;

}
void wGUI::addGUI(TLabel* label, TForm* Form){

    label->hwnd = CreateWindow(
                                    "static",
                                    label->__caption__,
                                    WS_CHILD | WS_VISIBLE,
                                    label->size.x, label->size.y,
                                    label->size.w, label->size.h,
                                    Form->hwnd,
                                    NULL,
                                    hI,
                                    NULL
                                 );

}
void wGUI::addGUI(TListBox* lb, TForm* Form){

    lb->hwnd = CreateWindow(
                                    "listbox",
                                    "",
                                    WS_CHILD | WS_VISIBLE | LBS_STANDARD| LBS_SORT,
                                    lb->size.x, lb->size.y,
                                    lb->size.w, lb->size.h,
                                    Form->hwnd,
                                    (HMENU)lb->id,
                                    hI,
                                    NULL
                                 );
    aTListBoxs[ lb->id ] = lb;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wP, LPARAM lP)
{
    switch( msg )
    {
        case WM_DESTROY:
                PostQuitMessage(0);
        break;
        case WM_COMMAND:
                wgui.EventListener(wP, lP);
        break;
        default:
                DefWindowProc(hwnd, msg, wP, lP);

    }
}

void wMessage(LPTSTR message, LPTSTR caption = wgui.__class__)
{
    MessageBoxA(0, message, caption, 0);
}

#endif // WGUI_H
