// Parallax.cpp
#include "Paralaxlayers.h"

// Fredik Zaar SP6 Demon Hunter

// struct ParallaxLayer
// ************************************************************

// ------------------------------------------------------------
// ParallaxLayer() - inits members
// ------------------------------------------------------------
ParallaxLayer::ParallaxLayer()
{
	m_parallax = 0;
	m_surface = m_surfaceYOffset = 0;
	m_width = m_height = 0;
	DX = 0;
	DY = 0;
	DW = 0;
	DH = 0;
	HowFarGone = 0;
	AnimClouds = 0;
}



// ------------------------------------------------------------
// set() - set members
// ------------------------------------------------------------
void ParallaxLayer::set( float p, int s, int sy, int w, int h, int DestX, int DestY,
									int DestW, int DestH  )
{
	m_parallax = p; 
	m_surface = s; 
	m_surfaceYOffset = sy; 
	m_width = w; 
	m_height = h; 
	DX = DestX;
	DY = DestY;
	DW = DestW;
	DH = DestH;
	Xpos = 0;
}





// class ParallaxBackground
// ************************************************************
// ------------------------------------------------------------
// ParallaxBackground() - inits members
// ------------------------------------------------------------
ParallaxBackground::ParallaxBackground()
{
	m_layerCount = 0;
	m_pLayers = 0;
}



// ------------------------------------------------------------
// ~ParallaxBackground() - cleans up
// ------------------------------------------------------------
ParallaxBackground::~ParallaxBackground()
{
	if( m_pLayers ) 
	{
		delete [] m_pLayers; 
	}
}



// ------------------------------------------------------------
// createLayers() - kills old layers and creates new ones
// ------------------------------------------------------------
void ParallaxBackground::createLayers( int count )
{
	// Kill old layers
	if( m_pLayers ) 
	{
		delete [] m_pLayers; 
	}


	// Create new layers
	m_layerCount = count;
	m_pLayers = new ParallaxLayer[ count ];
}



// ------------------------------------------------------------
// setLayer() - sets internal data for a layer
// ------------------------------------------------------------
void ParallaxBackground::setLayer(	int index, float p, int s, int sy, int w, int h, int DestX, int DestY,
									int DestW, int DestH )
{
	// Sanity check
	if( ( index < 0 ) || ( index >= m_layerCount ) )
		return;

	// Set it!
	m_pLayers[ index ].set( p, s, sy, w, h, DestX, DestY, DestW, DestH );
}



// ------------------------------------------------------------
// getLayer() - returns layer
// ------------------------------------------------------------
ParallaxLayer *ParallaxBackground::getLayer( int index )
{
	// Sanity check
	if( ( index < 0 ) || ( index >= m_layerCount ) )
	{
		return 0;
	}

	// Return it!
	return &m_pLayers[ index ];
}
