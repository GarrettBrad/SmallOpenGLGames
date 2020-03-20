#include "pch.h"
#include "Graphics.h"




// Made private for singleton
Graphics::Graphics()
{
}

// Releases all the graphics resources
Graphics::~Graphics()
{
	ReleaseResouces();
}

// Sets the member handle to the window handle
void Graphics::InitInter(HWND hWnd)
{
	m_hWnd = hWnd;

	CreateDeviceIndependentResource();

}
void Graphics::Init(HWND hWnd)
{
	Get().InitInter(hWnd);
}

// Returns the Direct2D render target
ID2D1HwndRenderTarget*& Graphics::GetRenderTargetInter()
{
	return pRenderTarget;
}
// Returns the Direct2D render target
ID2D1HwndRenderTarget*& Graphics::GetRenderTarget()
{
	return Get().GetRenderTargetInter();
}

// Gets the factory from graphics
ID2D1Factory* Graphics::GetFactoryInter()
{
	return pFactory;
}
// Returns the Direct2D factory
ID2D1Factory* Graphics::GetFactory()
{
	return Get().GetFactoryInter();
}

// The start of drawing
void Graphics::StartDrawInter()
{
	HRESULT hr = CreateGraphicsResources();

	if (SUCCEEDED(m_Hr))
	{
		pRenderTarget->BeginDraw();
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}

}
void Graphics::StartDraw()
{
	Get().StartDrawInter();
}

// End of drawing
void Graphics::EndDrawInter()
{
	m_Hr = pRenderTarget->EndDraw();

	if (m_Hr == D2DERR_RECREATE_TARGET)
	{
		m_Hr = S_OK;
		ReleaseResouces();
	}
}
void Graphics::EndDraw()
{
	Get().EndDrawInter();
}

// Resource methods

// Im pretty sure this is temp and i don't know what it does. Im just trying to get DirectX Working right now
void Graphics::CalculateLayout()
{
	// Copy paste from MSDN

	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

// This might stay. It looks like creates a resource to draw to
HRESULT Graphics::CreateGraphicsResources()
{
	// Copy paste from MSDN
	HRESULT hr = S_OK;
	if (!pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, size),
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{

			hr = pRenderTarget->CreateSolidColorBrush(m_DrawColor, &pBrush);

			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}
	}
	return hr;
}

HRESULT Graphics::CreateDeviceIndependentResource()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

	return hr;
}

// Frees all the resources we needed
void Graphics::ReleaseResouces()
{
	// Copy Paste
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}

// Called on window resize
void Graphics::ResizeInter()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(m_hWnd, NULL, FALSE);
	}
}
// Called on a window resize (I think its turned off right now)
void Graphics::Resize()
{
	Get().ResizeInter();
}

void Graphics::SetDrawColorInter(float& r, float& g, float& b)
{
	if (SUCCEEDED(m_Hr))
	{
		m_DrawColor = D2D1::ColorF(r, g, b);
		pRenderTarget->CreateSolidColorBrush(m_DrawColor, &pBrush);
	}
}
void Graphics::SetDrawColor(float r, float g, float b)
{
	Get().SetDrawColorInter(r, g, b);
}

// Draws a rectangle to screen
void Graphics::DrawRectInter(float& x1, float& y1, float& x2, float& y2, bool& fill)
{
	if (SUCCEEDED(m_Hr))
	{
		
		D2D1_RECT_F rec = D2D1::RectF(
			x1,
			y1,
			x2,
			y2
		);

		if (fill) {
			pRenderTarget->FillRectangle(rec, pBrush);
		} else {
			pRenderTarget->DrawRectangle(rec, pBrush);
		}

	}
}
void Graphics::DrawRect(float x1, float y1, float x2, float y2, bool fill)
{
	Get().DrawRectInter(x1, y1, x2, y2, fill);
}

// Will draw draws a grid
void Graphics::DrawGridInter(int& size)
{
	// Check We are ok to draw
	if (SUCCEEDED(m_Hr))
	{

		m_DrawSize = pRenderTarget->GetSize();

		int width = static_cast<int>(m_DrawSize.width);
		int height = static_cast<int>(m_DrawSize.height);

		// X
		for (int i = 0; i < width; i += size)
		{
			pRenderTarget->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(i), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(i), m_DrawSize.height),
				pBrush,
				0.5f
			);
		}

		// Y
		for (int i = 0; i < height; i += size)
		{
			pRenderTarget->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(i)),
				D2D1::Point2F(m_DrawSize.width, static_cast<FLOAT>(i)),
				pBrush,
				0.5f
			);
		}

		
	}
}
void Graphics::DrawGrid(int size)
{
	Get().DrawGridInter(size);
}

// Draws a line segment with the given points
void Graphics::DrawLineInter(Point& p1, Point& p2)
{
	if (SUCCEEDED(m_Hr))
	{


		m_DrawSize = pRenderTarget->GetSize();


		pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(p1.X), static_cast<FLOAT>(p1.Y)),
			D2D1::Point2F(static_cast<FLOAT>(p2.X), static_cast<FLOAT>(p2.Y)),
			pBrush,
			0.5f
		);

		
	}
}
void Graphics::DrawLine(Point x, Point y)
{
	Get().DrawLineInter(x, y);
}

// Gets the current instance of Graphics
Graphics& Graphics::Get()
{
	static Graphics graph;
	return graph;
}

