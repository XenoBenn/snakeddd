/* ======================================================================
   File: main.cpp
   Date : 2024-07-04
   Description : The main entry point.
   Creator : Benjamin Komar
   Notice : (C) Copyright 2024 by Teogo, Inc. All Rights Reserved.
   ======================================================================*/

#include "../../raylib-master/src/raylib.h"
#include "../../raylib-master/src/raymath.h"
#include <deque>
#include <iostream>


Color green = {173, 204, 96, 255};
Color dark_green = {43, 51, 24, 255};



const int cell_size = 30;
const int cell_count = 6;
const int cube_width = 2;

const int window_height = cell_size * cell_size;
const int window_width = cell_size * cell_size;


double last_updated_time = 0;

bool EventTriggered(double interval) {
	double current_time = GetTime();
	if ( current_time - last_updated_time >= interval ) {
		last_updated_time = current_time;
		return true;
	}
	return false;
}
	
class Food {

	public:
		Vector3 position;

		Food() {
			position = GenerateRandomPos();
			std::cout << position.x << '\n'
				      << position.y << '\n'
				      << position.z << '\n';
		}

		void Draw() {
			DrawCube(position, (float)cube_width, 2.0f, 2.0f, dark_green);
			DrawCubeWires(position, 2.0f, 2.0f, 2.0f, RED);
		}

		Vector3 GenerateRandomPos() {
			int x = GetRandomValue( (-1 * cell_count), cell_count - 1 );
			if (x % 2 != 0) {
				x = GetRandomValue( (-1 * cell_count), cell_count - 1 );
			}
			int y = GetRandomValue( (-1 * cell_count), cell_count - 1 );
			if (y % 2 != 0) {
				y = GetRandomValue( (-1 * cell_count), cell_count - 1 );
			}
			int z = GetRandomValue( (-1 * cell_count), cell_count - 1 );
			if (z % 2 != 0) {
				z = GetRandomValue( (-1 * cell_count), cell_count - 1 );
			}

			return Vector3{(float)x, (float)y, (float)z};
		}
};

class Snake {

	public:
		std::deque<Vector3> body = {Vector3{-4, 0, 2}, Vector3{-6, 0, 2}, Vector3{-8, 0, 2}};
		Vector3 direction = {2, 0, 0};

		void Draw() {
			for (unsigned int i = 0; i < body.size(); i++) {
				int x = body[i].x;
				int y = body[i].y;
				int z = body[i].z;
				DrawCube(Vector3{(float)x, (float)y, (float)z}, cube_width, 2.0f, 2.0f, BLUE);
				DrawCubeWires(Vector3{(float)x, (float)y, (float)z}, cube_width, 2.0f, 2.0f, BLACK);
			}
		}

		void Update() {
			body.pop_back();
			body.push_front(Vector3Add(body[0], direction));
		}
};

int main ()
{

	// set up the window
	InitWindow(window_height, window_width, "SnakeDDD");
	SetTargetFPS(60);

	Vector3 camera_position = { 0.0f, 20.0f, 14.0f };

	// Define the camera to look into the world
	Camera3D camera;
	camera.position = camera_position;
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 55.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Food food = Food();
	Snake snake = Snake();
	
	// game loop
	while (!WindowShouldClose())
	{

		// UpdateCamera(&camera, CAMERA_FREE);
		// if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

		// drawing
		BeginDrawing();

		if (EventTriggered(0.3)) {
			snake.Update();
		}

		if (IsKeyPressed(KEY_Q) && snake.direction.y != -2) {
			snake.direction = { 0, 2, 0 };
		}

		if (IsKeyPressed(KEY_E) && snake.direction.y != 2) {
			snake.direction = { 0, -2, 0 };
		}

		if (IsKeyPressed(KEY_D) && snake.direction.x != -2) {
			snake.direction = { 2, 0, 0 };
		}

		if (IsKeyPressed(KEY_A) && snake.direction.x != 2) {
			snake.direction = { -2, 0, 0 };
		}

		if (IsKeyPressed(KEY_S) && snake.direction.z != -2) {
			snake.direction = { 0, 0, 2 };
		}

		if (IsKeyPressed(KEY_W) && snake.direction.z != 2) {
			snake.direction = { 0, 0, -2 };
		}



	ClearBackground(RAYWHITE);

		BeginMode3D(camera);

			for (int i = -1 * cell_count; i < cell_count; i+=cube_width) {
				for (int j = -1 * cell_count; j < cell_count; j+=cube_width) {
					for (int k = -1 * cell_count; k < cell_count; k+=cube_width) {
						DrawCubeWires(Vector3{(float)i, (float)j, (float)k}, cube_width, 2.0f, 2.0f, GRAY);
					}
				}
			}

			food.Draw();
			snake.Draw();

			// DrawGrid(10, 1.0f);
			
		EndMode3D();

		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}
