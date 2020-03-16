#include "pch.h"
#include "Sprite.h"

#if _DEBUG
extern unsigned int g_UpDown;
extern unsigned int g_LeftRight;
#endif

// TODO Add scale
// Draws the sprite to screen
void Sprite::Draw(float posX, float posY, float scale, float alpha)
{
	if (m_Hr == S_OK)
	{
		m_Frame++; // Add one to the frame count 

		if (m_Count == 1)
		{
			// Actually renders the bitmap
			Graphics::GetRenderTarget()->DrawBitmap(
				m_Bmp,
				D2D1::RectF(posX,posY,posX + m_Size.width * scale,posY + m_Size.height * scale),// The bitmap area
				alpha,																			// alpha
				D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,// Draw closest pixel
				D2D1::RectF(0, 0, m_Bmp->GetSize().width, m_Bmp->GetSize().height)
			);
		}
		else
		{
			int DrawFrame = (m_Frame / 10) % m_Count; // Makes it switch slower

			Graphics::GetRenderTarget()->DrawBitmap(
				m_Bmp,
				D2D1::RectF(
					posX,
					posY,
					posX + m_Size.width * scale,
					posY + m_Size.height * scale
				),	// The bitmap area
				1.0f,	// alpha
				D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,// closest pixel
				D2D1::RectF(
					(DrawFrame % m_Count) * (m_Size.width + m_DistanceBetweenFames) + m_Offset,
					(DrawFrame / m_Count) * m_Size.height,
					((DrawFrame % m_Count) * (m_Size.width + m_DistanceBetweenFames)) + m_Size.width + m_Offset,
					((DrawFrame / m_Count) * m_Size.height) + m_Size.height
				)
			);
		}
	}
}

[[deprecated]]
const D2D1_SIZE_F& Sprite::GetSize() const
{
	return m_Size;
}

void Sprite::ConstructSprite(ImageInfo& image)
{
	// Stops a crash when closing the application
	m_Hr = CoInitialize(nullptr);

	if (FAILED(m_Hr))  return;

	IWICImagingFactory* wicFactory = NULL;
	m_Hr = CoCreateInstance(
		CLSID_WICImagingFactory, // What we are making
		NULL,					 // Not part of an aggregate
		CLSCTX_INPROC_SERVER,	 // DLL runs in the same thread
		IID_PPV_ARGS(&wicFactory)
	);

	if (FAILED(m_Hr)) return;

	IWICBitmapDecoder* wicDecoder = NULL;
	m_Hr = wicFactory->CreateDecoderFromFilename(
		image.file,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder
	);

	if (FAILED(m_Hr)) return; // TODO add error handling

	IWICBitmapFrameDecode* wicFrame = NULL;
	m_Hr = wicDecoder->GetFrame(0, &wicFrame);

	// Flips the image 
	// It doesn't work and i don't know why
	IWICBitmapFlipRotator* pIFlipRotator = NULL;
	if (image.flipped)
	{

		m_Hr = wicFactory->CreateBitmapFlipRotator(
			&pIFlipRotator);

		if (FAILED(m_Hr)) return;

		m_Hr = pIFlipRotator->Initialize(
			wicFrame,
			WICBitmapTransformFlipHorizontal
		);

	}

	if (FAILED(m_Hr)) return;

	IWICFormatConverter* wicConvert = NULL;
	m_Hr = wicFactory->CreateFormatConverter(&wicConvert);

	if (FAILED(m_Hr)) return;

	m_Hr = wicConvert->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	if (FAILED(m_Hr)) return;

	// This doesn't work and I don't know why
	m_Hr = Graphics::GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConvert,
		NULL,
		&m_Bmp
	);

	if (FAILED(m_Hr)) return;

	// Release all the resources
	if (wicDecoder) wicDecoder->Release();
	if (wicFrame) wicFrame->Release();
	if (wicConvert) wicConvert->Release();
	if (pIFlipRotator) pIFlipRotator->Release();
	if (wicFactory) wicFactory->Release();
}

// Creates the sprite with the animation image
Sprite::Sprite(ImageInfo image, int width, int height, int count)
	: m_Bmp(NULL), m_Size({ (float)width, (float)height }), m_Count(count)
{
	// TODO: Make this do the thing I want C:
	ConstructSprite(image);
}

// TODO: Add error Handling
// Creates the bitmap for the sprite
Sprite::Sprite(ImageInfo image)
	: m_Bmp(NULL)
{
	ConstructSprite(image);
	m_Size = m_Bmp->GetSize();

	m_Size.width;
	m_Size.height;
}

// Cleanup
Sprite::~Sprite()
{
	if (m_Bmp)
		m_Bmp->Release();

	m_Bmp = NULL;
}
