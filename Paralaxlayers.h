// Parallax.h
#pragma once
#include "SDL.h"

// Fredik Zaar SP6 Demon Hunter

// struct declarations
struct ParallaxLayer
{
	ParallaxLayer();
	void set(	float p, int s, int sy, int w, int h, int DestX, int DestY,
				int DestW, int DestH  );


	float m_parallax;
	int m_surface, m_surfaceYOffset;
	int m_width, m_height;
	int DX, DY, DW, DH;
	int Xpos;
	int HowFarGone;
	int AnimClouds;
};



// ParallaxBackground - container for ParallaxLayer
// ------------------------------------------------
class ParallaxBackground
{
	public:	
		ParallaxBackground();
		~ParallaxBackground();

		// Creation
		void createLayers( int count );

		// Get/Set
		int getLayerCount() { return m_layerCount; }
		ParallaxLayer *getLayer( int index );
		void setLayer(	int index, float p, int s, int sy, int w, int h, int DestX, int DestY,
						int DestW, int DestH );


	private:
		int m_layerCount;
		ParallaxLayer *m_pLayers;
};
