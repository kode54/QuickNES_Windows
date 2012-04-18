#include "stdafx.h"
#include "display.h"

#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <stdint.h>

template <typename T>
inline void SafeRelease(T& p)
{
	if (NULL != p)
	{
		p.Release();
		p = NULL;
	}
}



class display_d2d : public display
{
protected: 

	HWND window_hwnd;
	int scwidth;
	int scheight;
	int prevwidth;
	int prevheight;

	bool waiting;

	void * locked_framebuffer;

	ID2D1Factory * m_d2dFactory;
	HMODULE m_hD2D1Lib;
	CComPtr<ID2D1HwndRenderTarget>  m_hWndTarget;
	CComPtr<ID2D1Bitmap>            m_bitmap; 
	BITMAPINFOHEADER m_pBitmapInfo;

	int createrendbmp(int width, int height, bool wait)
	{
		if (prevwidth == width && prevheight == height && wait == waiting)
			return 0;

		D2D1_PIXEL_FORMAT pixelFormat = 
		{ 
			DXGI_FORMAT_B8G8R8A8_UNORM ,
			D2D1_ALPHA_MODE_IGNORE
		};
		D2D1_RENDER_TARGET_PROPERTIES renderTargetProps = 
		{
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			pixelFormat,
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		};

		RECT rect;
		GetClientRect(window_hwnd, &rect);
		HRESULT hr;
		D2D1_SIZE_U windowSize = 
		{
			rect.right - rect.left,
			rect.bottom - rect.top
		};

		D2D1_HWND_RENDER_TARGET_PROPERTIES hWndRenderTargetProps = 
		{
			window_hwnd,
			windowSize,
			wait ? D2D1_PRESENT_OPTIONS_NONE : D2D1_PRESENT_OPTIONS_IMMEDIATELY 
		};
		SafeRelease(m_hWndTarget);
		hr = m_d2dFactory->CreateHwndRenderTarget(renderTargetProps, hWndRenderTargetProps, &m_hWndTarget);
		if (hr != S_OK) return -1;
		FLOAT dpiX, dpiY;
		m_d2dFactory->GetDesktopDpi(&dpiX, &dpiY);
		D2D1_BITMAP_PROPERTIES bitmapProps = 
		{
			pixelFormat,
			dpiX,
			dpiY
		};

		D2D1_SIZE_U bitmapSize = 
		{
			width,
			height
		};
		prevwidth=width;
		prevheight=height;
		waiting=wait;
		SafeRelease(m_bitmap);
		hr = m_hWndTarget->CreateBitmap(bitmapSize, bitmapProps, &m_bitmap);
		if (hr != S_OK) return -1;
		return 0;
	}

public:
	display_d2d()
	{
		m_bitmap = NULL;
		m_d2dFactory = NULL;
		m_hWndTarget = NULL;
		m_hD2D1Lib = NULL;
		locked_framebuffer = NULL;
	}

	virtual ~display_d2d()
	{
		if (locked_framebuffer) free(locked_framebuffer);
		SafeRelease(m_bitmap);
		SafeRelease(m_hWndTarget);
		if (m_d2dFactory) m_d2dFactory->Release();
		FreeLibrary(m_hD2D1Lib);
	}

	virtual const char* open( unsigned buffer_width, unsigned buffer_height, HWND hWnd )
	{
		m_hD2D1Lib = LoadLibrary(L"D2D1.DLL");
		if (m_hD2D1Lib)
		{
			typedef HRESULT(STDAPICALLTYPE* FPCF)(D2D1_FACTORY_TYPE, REFIID, CONST D2D1_FACTORY_OPTIONS *, void**);
			FPCF pfn = (FPCF) GetProcAddress(m_hD2D1Lib, "D2D1CreateFactory");
			if (pfn == NULL || FAILED(pfn(D2D1_FACTORY_TYPE_SINGLE_THREADED,IID_ID2D1Factory, NULL, (void**)&m_d2dFactory)))
			{
				m_d2dFactory = nullptr;
				return "creating D2D factory";
			}
		}
		else return "opening D2D1.DLL";

		window_hwnd = hWnd;
		scwidth = buffer_width, scheight = buffer_height;
		prevheight = prevwidth = 0;

		if ( createrendbmp( 1, 1, false ) == -1 ) return "creating render bitmap";

		clear();

		return 0;
	}

	virtual void update_position()
	{
	}

	virtual const char* lock_framebuffer( void *& buffer, unsigned & pitch )
	{
		if ( !locked_framebuffer ) locked_framebuffer = malloc( scwidth * scheight * 4 );
		buffer = locked_framebuffer;
		pitch = scwidth * 4;
		return 0;
	}

	virtual const char* unlock_framebuffer()
	{
		return 0;
	}

	virtual const char* paint( bool wait )
	{
		HRESULT hr;
		if (createrendbmp(scwidth, scheight, wait) == -1)
			return "creating backbuffer bitmap";
		if ( locked_framebuffer )
		{
			hr = m_bitmap->CopyFromMemory(NULL, locked_framebuffer, scwidth*4);
			if (hr != S_OK) return "copying to bitmap";
		}
		repaint();
		return 0;
	}

	void do_repaint(bool blit)
	{
		if (!(m_hWndTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			RECT rect;
			GetClientRect(window_hwnd, &rect);
			D2D1_SIZE_U newSize = { rect.right, rect.bottom };
			D2D1_SIZE_U size = m_hWndTarget->GetPixelSize();

			if(newSize.height != size.height || newSize.width != size.width)
			{
				m_hWndTarget->Resize(newSize);
			}
			D2D1_RECT_F rectangle = D2D1::RectF(0, 0, newSize.width, newSize.height);
			m_hWndTarget->BeginDraw();
			m_hWndTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
			if (blit) m_hWndTarget->DrawBitmap(m_bitmap, rectangle,1.0f,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
			m_hWndTarget->EndDraw();
			ValidateRect(window_hwnd,NULL);
		}
	}

	virtual void repaint()
	{
		do_repaint(true);
	}

	virtual void clear()
	{
		do_repaint(false);
	}
};

display * create_display_d2d()
{
	return new display_d2d;
}
