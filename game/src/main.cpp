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



int main ()
{
	const int window_height = 1280;
	const int window_width = 800;

	// set up the window
	InitWindow(window_height, window_width, "Scholaris");

	Vector3 camera_position = { 0.0f, 10.0f, 10.0f };

	// Define the camera to look into the world
	Camera3D camera;
	camera.position = camera_position;
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 cube_position = {0.0f, 0.0f, 0.0f};
	
	// game loop
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
			DrawCube(cube_position, 2.0f, 2.0, 2.0f, GRAY);
			DrawCubeWires(cube_position, 2.0f, 2.0, 2.0f, RED);

			DrawGrid(10.0f, 10.0f);
		EndMode3D();

		DrawText("Hello Raylib", 200,200,20,WHITE);

		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}
