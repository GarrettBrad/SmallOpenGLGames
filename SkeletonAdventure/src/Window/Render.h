#ifndef RENDER_H
#define RENDER_H


// Game tell Render what to render
// Render Tells Graphics how to render
// Graphics makes the graphics
//
// This is for larger objects such as a skeleton or other.
// for lines and other stuff Graphics can be called directly
class Render
{
private:


	Render();

	void InitInter(HWND wnd);

	void StartRenderInter();


	void EndRenderInter();

public:

	static void Init(HWND wnd);

	static void StartRender();


	static void EndRender();

	static Render& Get();

};

#endif /* RENDER_H*/
