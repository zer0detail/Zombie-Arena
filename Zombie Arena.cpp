#include <SFML\Graphics.hpp>
#include "player.h"
#include <iostream>

using namespace sf;

int main() {
	// The game will always be in one of four states
	enum class State {
		PAUSED, 
		LEVELING_UP,
		GAME_OVER,
		PLAYING
	};

	// Start with the GAME_OVER  state
	State state = State::GAME_OVER;
	// Get the screen resolution and
	// create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(
		VideoMode(resolution.x, resolution.y),
		"Zombie Arena",
		Style::Fullscreen
	);

	// Create an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;
	// Where is the mouse in relation to the world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to the screen coordinates
	Vector2i mouseScreenPosition;
	// Create an instance of the player class
	Player player;
	// The boundaries of the arena
	IntRect arena;
	// Main game loop
	while (window.isOpen()) {
		/**********
		 Handle Input
		**********/
		// Handle events by polling
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				// Pause a game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					std::cout << "State change: State::PAUSED";
					state = State::PAUSED;
				}
				// Restart while paused
				else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
					std::cout << "State change: State::PLAYING";
					state = State::PLAYING;
					// Reset the clock so there isnt a frame jump
					clock.restart();
				}
				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					std::cout << "State change: State::LEVELING_UP";
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING) {

				}
			}
		} // End event polling

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		// Handle WASD while playing
		if (state == State::PLAYING) {
			//Handle the pressing and releasing oF WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.moveUp();
			}
			else {
				player.stopUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.moveDown();
			}
			else {
				player.stopDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.moveLeft();
			}
			else {
				player.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player.moveRight();
			}
			else {
				player.stopRight();
			}
		} // End WASD Checks
		// Handle the LEVELING up state
		if (state == State::LEVELING_UP) {
			// Handle the player LEVELING up
			if (event.key.code == Keyboard::Num1) {
				std::cout << "State change: State::PLAYING";
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}

			if (state == State::PLAYING) {
				// Prepare the level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				int tileSize = 50;
				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		} // End leveling up

		/************
		  UPDATE THE FRAME
		************/
		if (state == State::PLAYING) {
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;

			// Make a decimal fraction of 1 from the delta time
			float dtAsSecond = dt.asSeconds();
			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();
			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(),
				mainView
			);
			// Update the player
			player.update(dtAsSecond, Mouse::getPosition());
			// Make a note of the player new position
			Vector2f playerPosition(player.getCenter());
		} // End scene update
		/*************
		  DRAW THE SCENE
		**************/
		if (state == State::PLAYING) {
			window.clear();
			// Set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);
			// Draw the player
			window.draw(player.getSprite());
		}
		if (state == State::LEVELING_UP) {

		}
		if (state == State::PAUSED) {

		}
		if (state == State::GAME_OVER) {

		}
		window.display();
	} // End game loop
	return 0;
}