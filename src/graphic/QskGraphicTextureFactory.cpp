/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#include "QskGraphicTextureFactory.h"
#include "QskTextureRenderer.h"

#include <qquickwindow.h>

QskGraphicTextureFactory::QskGraphicTextureFactory()
{
}

QskGraphicTextureFactory::QskGraphicTextureFactory(
        const QskGraphic& graphic, const QSize& size )
    : m_graphic( graphic )
    , m_size( size )
{
}

QskGraphicTextureFactory::~QskGraphicTextureFactory()
{
}

QSGTexture* QskGraphicTextureFactory::createTexture( QQuickWindow* window ) const
{
    const uint textureId = QskTextureRenderer::createTextureFromGraphic(
        QskTextureRenderer::OpenGL, m_size, m_graphic, m_colorFilter,
        Qt::IgnoreAspectRatio );

    const auto flags = static_cast< QQuickWindow::CreateTextureOptions >(
        QQuickWindow::TextureHasAlphaChannel | QQuickWindow::TextureOwnsGLTexture );

#if QT_VERSION >= QT_VERSION_CHECK( 5, 14, 0 )
    const int nativeLayout = 0; // VkImageLayout in case of Vulkan

    return window->createTextureFromNativeObject( 
        QQuickWindow::NativeObjectTexture, &textureId, nativeLayout,
        m_size, flags );
#else
    return window->createTextureFromId( textureId, m_size, flags );
#endif
}

QSize QskGraphicTextureFactory::textureSize() const
{
    return m_size;
}

int QskGraphicTextureFactory::textureByteCount() const
{
    return m_size.width() * m_size.height() * 4;
}

QImage QskGraphicTextureFactory::image() const
{
    return m_graphic.toImage( m_size, Qt::KeepAspectRatio );
}
