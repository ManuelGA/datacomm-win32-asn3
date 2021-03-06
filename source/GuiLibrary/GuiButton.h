#ifndef _GUI_BUTTON_H_
#define _GUI_BUTTON_H_

#define WIN32_LEAN_AND_MEAN

#include "GuiComponent.h"

class GuiButton : public GuiComponent
{
public:
	GuiButton(HINSTANCE hInstance, GuiComponent *parent, UINT id);

	void setText(LPCWSTR text);
	virtual HWND create(HINSTANCE hInstance, HWND parent);

private:
	UINT id;
	bool registerWindowsClass(HINSTANCE hInstance);
};

#endif