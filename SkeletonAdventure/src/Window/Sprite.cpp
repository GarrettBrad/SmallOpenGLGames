#include "pch.h"
#include "Sprite.h"

// TODO Add scale
// Draws the sprite to screen
void Sprite::Draw(float posX, float posY, float scale)
{
	if (m_Hr == S_OK)
	{
		m_Size = m_Bmp->GetSize();

		m_Size.width *= scale;
		m_Size.height *= scale;

		// Actually renders the bitmap
		Graphics::GetRenderTarget()->DrawBitmap(
			m_Bmp,
			D2D1::RectF(posX, posY, posX + m_Size.width, posY + m_Size.height),				// The bitmap area
			1.0f,																			// alpha
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,// Draw closest pixel
			D2D1::RectF(0, 0, SKEL_WINDOW_WIDTH, SKEL_WINDOW_HEIGHT)						// Wherer the sprite can be draw
		);
	}
}

[[deprecated]]
const D2D1_SIZE_F& Sprite::GetSize() const
{
	return m_Size;
}

// TODO: Add error Handling
// Creates the bitmap for the sprite
Sprite::Sprite(ImageInfo image)
	: m_Bmp(NULL)
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

// Cleanup
Sprite::~Sprite()
{
	if (m_Bmp)
		m_Bmp->Release();

	m_Bmp = NULL;
}
