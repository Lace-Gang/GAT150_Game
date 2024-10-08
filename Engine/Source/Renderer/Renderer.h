#pragma once

#include "Math/Vector2.h"

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include<memory>

class Texture;

class Renderer
{
public:
	Renderer() = default;

	bool Initialize(); 
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);   //uint8_t "typedef unsigned char" (gives you only up to 255)
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);
	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);
	//void DrawCircle(float x, float y, float r);

	void DrawTexture(std::weak_ptr<class Texture> texture, float x, float y, float angle = 0.0f);
	void DrawTexture(std::weak_ptr<class Texture> texture, const struct Transform& transform, bool hflip = false);
	void DrawTexture(std::weak_ptr<class Texture> texture, const struct Transform& transform, const struct Rect& srcRect, bool hflip = false);



	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	friend class Text;
	friend class Texture;
private:
	SDL_Window* m_window{ nullptr }; 
	SDL_Renderer* m_renderer{ nullptr };

	int m_width = 0;
	int m_height = { 0 };
};