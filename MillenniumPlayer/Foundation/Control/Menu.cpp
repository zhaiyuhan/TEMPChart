#include "stdafx.h"
#include "Menu.h"

#pragma comment (lib,"Dwmapi.lib")
Menu::Menu(QWidget *parent)
	: QMenu(parent)
{
	QFile maintheme(":/MainView/Resources/NormalTheme.qss");
	if (maintheme.open(QFile::ReadOnly))
	{
		QString style = QLatin1String(maintheme.readAll());
		this->setStyleSheet(style);
		maintheme.close();
	}
}

Menu::Menu(const QString &title) :
	QMenu(title)
{

}



bool Menu::event(QEvent *event)
{
	static bool class_amended = false;
	if (event->type() == QEvent::WinIdChange)
	{
		HWND hwnd = reinterpret_cast<HWND>(winId());
		if (class_amended == false)
		{
			class_amended = true;
			DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
			class_style &= ~CS_DROPSHADOW;
			::SetClassLong(hwnd, GCL_STYLE, class_style);
		}
		DWMNCRENDERINGPOLICY val = DWMNCRP_ENABLED;
		::DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &val, sizeof(DWMNCRENDERINGPOLICY));
		MARGINS m = { -1 };
		HRESULT hr = ::DwmExtendFrameIntoClientArea(hwnd, &m);
		if (SUCCEEDED(hr))
		{
			//do more things
		}
		HMODULE hUser = GetModuleHandle(L"user32.dll");
		if (hUser)
		{
			pfnSetWindowCompositionAttribute setWindowCompositionAttribute =
				(pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
			if (setWindowCompositionAttribute)
			{
				ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
				WINDOWCOMPOSITIONATTRIBDATA data;
				data.Attrib = WCA_ACCENT_POLICY;
				data.pvData = &accent;
				data.cbData = sizeof(accent);
				setWindowCompositionAttribute(hwnd, &data);
			}
		}
	}
	return QWidget::event(event);
}
