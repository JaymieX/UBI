//-----------------------------------------------------------------------------
// SimpleSprite.h
// Privides a very simple DSOUND wrapper to load and play wav files.
//-----------------------------------------------------------------------------
#ifndef _SIMPLESPRITE_H_
#define _SIMPLESPRITE_H_

#include "../glut/include/GL/freeglut.h"
#include <map>
#include <vector>

//-----------------------------------------------------------------------------
// CSimpleSprite
//-----------------------------------------------------------------------------
class CSimpleSprite
{
public:
    // If width, height and UV coords are not provided then they will be derived from the texture size.
    CSimpleSprite(const char *fileName);
	// Draw, call from your game draw function.
    void Draw();
	// Sets and Gets for the various attributes of the sprite.
    void SetPosition(float x, float y) { m_xpos = x; m_ypos = y; }   
    void SetAngle(float a)  { m_angle = a; }
    void SetScale(float s) { m_scale = s; }
    
	void GetPosition(float &x, float &y) { x = m_xpos; y = m_ypos; }
    float GetWidth()  const { return m_width;  }
    float GetHeight() const { return m_height; }
    float GetAngle()  const { return m_angle;  }
    float GetScale()  const { return m_scale;  }    

	// Set the sprite color. r,g,b for color and a= the alpha value (Fade).
	void SetColor(float r, float g, float b, float a = 1.0f) { m_red = r; m_green = g; m_blue = b; m_alpha = a; }

	//------------------------------------------------------------
	// Advanced:
	//------------------------------------------------------------
	// Directly set the local coordinates of the sprite.
	// Use only if you want to have and not uniform sprite. Skewing or perspective can be achieved using this.
	void SetVertex(unsigned int i, float v) { if(i < 8) m_points[i] = v; }
	float GetVertex(unsigned int i) { if (i >= 8) i = 0; return m_points[i]; }

private:
    void CalculateUVs();
    GLuint m_texture;
    float m_xpos = 0.0F;
    float m_ypos = 0.0F;
    float m_width = 0.0F;
    float m_height = 0.0F;
    unsigned int   m_texWidth = 0;
    unsigned int   m_texHeight = 0;
    float m_angle = 0.0F;
    float m_scale = 1.0F;
    float m_points[8];    
    float m_uvcoords[8];
	float m_red = 1.0f;
	float m_green = 1.0f;
	float m_blue = 1.0f;
	float m_alpha = 1.0f;


    // Texture management.
    struct sTextureDef
    {
        unsigned int m_width;
        unsigned int m_height;
        GLuint m_textureID;
    };
    bool LoadTexture(const char*);
    static std::map<const char *, sTextureDef > m_textures;
    
};

#endif