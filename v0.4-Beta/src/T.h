#ifndef T_H
    #define T_H
#define wCheckBox 1
#define wMemo 1

struct TSize{
    UINT    w;
    UINT    h;
    int     x;
    int     y;
};


int wGUINumber = 0;


class TForm{
public:
    HWND hwnd;
    LPTSTR __caption__;
    TSize size = {500, 400, 0, 0};



    void Show(){
        ShowWindow(hwnd, SW_SHOW);
    }
    void Hide()
    {
        ShowWindow(hwnd, SW_HIDE);
    }
    void Minimize()
    {
        ShowWindow(hwnd, SW_MINIMIZE);
    }
    void Maximize()
    {
        ShowWindow(hwnd, SW_MAXIMIZE);
    }
    void Focus()
    {
        SetFocus(hwnd);
    }
};


class TObjectParent
{
public:
    HWND hwnd;
    LPTSTR __caption__;
    UINT id;
};



class TButton extends TObjectParent
{
public:
    TSize size = {120, 35, 0, 0};
    LPTSTR __classname__;

    void (*onClick)( TButton* ) = NULL;
    void (*onDblClick)( TButton* ) = NULL;

    TButton( LPTSTR caption = "button", int isCheckBox = 0 )
    {
        this->__caption__ = caption;
        this->id = wGUINumber++;
        if( isCheckBox == 1 )
                this->__classname__ = "checkbox";
        else
                this->__classname__ = "button";
    }
};
class TEdit extends TObjectParent
{
public:
    TSize size{120, 20, 0, 0};
    LPTSTR __classname__ = "3";

    void (*onChange)( TEdit*, char* ) = NULL;

    TEdit( LPTSTR caption = "edit", int isMemo = 0 )
    {
        if( isMemo == 1 ){
            this->__classname__ = "memo";
            this->size.w = 200;
            this->size.h = 100;
        }else
            this->__classname__ = "edit";
        this->__caption__ = caption;
        this->id = wGUINumber++;
    }



    char *Text(LPTSTR caption = "")
        {
                    if( caption == "" ){
                        char chBuf[ 10 ] = "0";
                        SendMessageA(hwnd, EM_GETLINE, 0, LPARAM( chBuf ));
                        return chBuf;
                    }else
                        SendMessage(hwnd, WM_SETTEXT, 0, LPARAM( caption ));

        }
    void setWord( LPTSTR word )
    {
        SendMessage(hwnd, EM_SETPASSWORDCHAR, WPARAM(word), 0);
    }
    void maxLenght(int max)
    {
        SendMessage(hwnd, EM_LIMITTEXT, max, 0);
    }
    void enable(bool i){
        if(!i)
            SendMessage(hwnd, EM_SETREADONLY, ES_READONLY, true);
        else
            SendMessage(hwnd, EM_SETREADONLY, false, false);
    }
};
class TListBox extends TObjectParent
{
public:
    TSize size{120, 150, 0, 0};

    TListBox()
    {
        this->id = wGUINumber++;
    }
    void addLine( char* text )
    {
        SendMessageA(hwnd, LB_ADDSTRING, 0, LPARAM(text));
    }
    void DeleteLine( int id )
    {
        SendMessageA(hwnd, LB_DELETESTRING, 0, id);
    }
};
class TLabel extends TObjectParent
{
public:
    TSize size = { 120, 35, 0, 0 };

    TLabel(LPTSTR caption = "label")
    {
        this->id = wGUINumber++;
        this->__caption__ = caption;
    }
};
/*class TMemo extends TObjectParent
{
public:
    TSize size = {200, 100, 0, 0};

    TMemo( LPTSTR caption = "memo" )
    {
        this->__caption__ = caption;
        this->id = wGUINumber++;
    }
};*/
#endif // T_H
