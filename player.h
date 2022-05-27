#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	// Where is the player
	Vector2f m_Position;
	// Declare the players sprite
	Sprite m_Sprite;
	// And a texture for the sprite
	Texture m_Texture;
	// What is the screen resolution
	Vector2f m_Resolution;
	// What size is the current arena
	IntRect m_Arena;
	// How big each tile of the arena
	int m_TileSize;
	// Which direction(s) is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
	// How much health has the current player got?
	int m_health;
	// What is the maximum health the player can have
	int m_maxHealth;
	// When was the player last hit
	Time m_LastHit;
	// Speed in pixels per second
	float m_Speed;
};