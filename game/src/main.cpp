/* ======================================================================
   File: main.cpp
   Date : 2024-07-04
   Description : The main entry point.
   Creator : Benjamin Komar
   Notice : (C) Copyright 2024 by Teogo, Inc. All Rights Reserved.
   ======================================================================*/

#include "../../raylib-master/src/raylib.h"
#include <deque>
#include <iostream>


Color green = {173, 204, 96, 255};
Color dark_green = {43, 51, 24, 255};

const int cell_size = 30;
const int cell_count = 5;

const int window_height = cell_size * cell_size;
const int window_width = cell_size * cell_size;
	
class Food {

	public:
		Vector3 position;

		Food() {
			position = GenerateRandomPos();
			std::cout << position.x;
		}

		void Draw() {
			DrawCube(position, 2.0f, 2.0f, 2.0f, dark_green);
			DrawCubeWires(position, 2.0f, 2.0f, 2.0f, RED);
		}

		Vector3 GenerateRandomPos() {
			float x = GetRandomValue( 0, cell_count - 1 );
			float y = GetRandomValue( 0, cell_count - 1 );
			float z = GetRandomValue( 0, cell_count - 1 );
			return Vector3{x, y, z};
		}
};

int main ()
{

	// set up the window
	InitWindow(window_height, window_width, "SnakeDDD");

	Vector3 camera_position = { 0.0f, 20.0f, 14.0f };

	// Define the camera to look into the world
	Camera3D camera;
	camera.position = camera_position;
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 55.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Food food = Food();
	
	// game loop
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
			food.Draw();

			for (int i = -1 * cell_count; i < cell_count; i+=2) {
				for (int j = -1 * cell_count; j < cell_count; j+=2) {
					for (int k = -1 * cell_count; k < cell_count; k+=2) {
						DrawCubeWires(Vector3{(float)i, (float)j, (float)k}, 2.0f, 2.0f, 2.0f, GRAY);
					}
				}
			}
			// DrawGrid(10, 1.0f);
		EndMode3D();

		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}
