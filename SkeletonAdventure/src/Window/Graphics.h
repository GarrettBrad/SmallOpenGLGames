#ifndef GRAPHICS_H
#define GRAPHICS_H

struct Point
{
	int X = 0;
	int Y = 0;

	Point() {}
	Point(int x, int y)
		: X(x), Y(y)
	{ }
};

class Graphics
{
private:

	HWND m_hWnd;

	PAINTSTRUCT ps;
	HDC hdc;
	D2D1_COLOR_F m_DrawColor = D2D1::ColorF(1.0f, 1.0f, 0);

	D2D1_SIZE_F m_DrawSize;

	ID2D1Factory* pFactory = NULL;
	ID2D1HwndRenderTarget* pRenderTarget = NULL;
	ID2D1SolidColorBrush* pBrush = NULL;

	D2D1_ELLIPSE ellipse;

	HRESULT m_Hr = S_OK;

	// Memory Management
	template<typename T>
	void SafeRelease(T** ptr)
	{
		if (*ptr)
		{
			(*ptr)->Release();
			*ptr = NULL;
		}
	}

	void InitInter(HWND hWnd);

	ID2D1HwndRenderTarget* GetRenderTargetInter();
	ID2D1Factory* GetFactoryInter();

	void StartDrawInter();
	void EndDrawInter();

	HRESULT CreateGraphicsResources();
	HRESULT CreateDeviceIndependentResource();

	void CalculateLayout();

	void ResizeInter();
	void OnRenderInter();

	void ReleaseResouces();

	void SetDrawColorInter(float& r, float& g, float& b);

	void DrawPictureInter(std::string& pic);

	void DrawCircleInter();
	void DrawRectInter(int& x1, int& y1, int& x2, int& y2, bool& fill);
	void DrawGridInter(int& size);
	void DrawLineInter(Point& x, Point& y);

	Graphics();
	~Graphics();
public:

	static void Init(HWND hWnd);

	static void Resize();
	static void OnRender();

	static ID2D1HwndRenderTarget* GetRenderTarget();
	ID2D1Factory* GetFactory();

	static void StartDraw();
	static void EndDraw();

	static void SetDrawColor(float r, float g, float b);

	// The main graphics stuff
	static void DrawPicture(std::string pic);
	
	static void DrawCircle();
	static void DrawRect(int x1, int y1, int x2, int y2, bool fill = true);
	static void DrawGrid(int size = 10);
	static void DrawLine(Point x, Point y);


	static Graphics& Get();
};

#endif /* GRAPHICS_H */
