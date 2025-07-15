#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/raylib.h"

struct box {

	Vector2 position;
	Vector2 size;
	Vector2 speed;
	int score;

};


char* concat(const char* s1, const char* s2){
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	
if (result == NULL) {
	printf("ptr allocation error");
	exit(-1);
}

	strcpy(result, s1);
	strcat(result, s2);
	return result;

}
int main() {
printf("hi :3");

int const screenWidth = 800;
int const screenHeight = 600;
InitWindow(screenWidth, screenHeight, "kitty");
SetTargetFPS(60);

bool pause = false;
bool collision = false;
bool loose = false;
bool win = false;

 
char *enemyScoreBuffer = malloc(256);
char *playerScoreBuffer = malloc(256);
char *colon = ":";

if (enemyScoreBuffer == NULL|| playerScoreBuffer == NULL || colon == NULL) {
	printf("ptr allocation error");
	return -1;

}
struct box player = {
	{(float)screenWidth/2, (float)screenHeight/2},
	{50, 50},
	{0.0f, 0.0f},
	0
};
struct box enemy = {
	{(float)0, (float)0},
	{40, 40},
	{0.0f, 0.0f},
	0
};
struct box ball = {

	{(float)screenWidth/2, (float)screenHeight/2},
	{10, 10},
	{4.5f, 4.5f},
	0
};
while (!WindowShouldClose()){

if (loose) DrawText("YOU LOST :(", screenWidth/2, screenHeight/2, 30, RED);

// UPDATE
//-----------------------------------------------------------
if (ball.position.x <= 0 || ball.position.x + ball.size.x >= screenWidth) ball.speed.x *= -1;



if (IsKeyPressed(KEY_SPACE)) pause = !pause;
if (enemy.score > player.score + 2) loose = true;
if (player.score > enemy.score + 2) win = true;
if (IsKeyPressed(KEY_R)){
// implement a resetting feature
	enemy.score = 0;
	player.score = 0;
	loose = false;
	win = false;
	ball.position.x = screenWidth/2;
	ball.position.y = screenHeight/2;

}
if (!pause && !loose && !win) {
	player.position.x = GetMouseX() - player.size.x/2;
	player.position.y = screenHeight - player.size.y;
	enemy.position.x = ball.position.x + (ball.size.x/2 - enemy.size.x/2);
	ball.position.x += ball.speed.x;
	ball.position.y += ball.speed.y;
}

// implement behavior of the ball and collision

// implement scoring system
sprintf(enemyScoreBuffer, "%d", enemy.score);
sprintf(playerScoreBuffer, "%d", player.score);
char* scoreText = concat(enemyScoreBuffer, colon);
scoreText = concat(scoreText, playerScoreBuffer);
if (ball.position.y >= screenHeight){
	enemy.score = enemy.score + 1;
	ball.position.x = screenWidth/2;
	ball.position.y = screenHeight/2;
}	
if (ball.position.y + ball.size.y == screenHeight - ball.size.y){
	player.score = player.score + 1;
	ball.position.x = screenWidth/2;
	ball.position.y = screenHeight/2;
}



if (collision) ball.speed.y *= -1;

//DRAW
//-----------------------------------------------------------


BeginDrawing();
ClearBackground(GRAY);
DrawText("MEOW!", 100, 200, 5, BLACK);
DrawFPS(0, 0);

DrawRectangleV(player.position, player.size, BLACK);
DrawRectangleV(enemy.position, enemy.size, YELLOW);
DrawRectangleV(ball.position, ball.size, RED);

if (loose) DrawText("YOU LOST :(", screenWidth/2, screenHeight/2, 30, RED);
if (win) DrawText("YOU WIN :3", screenWidth/2, screenHeight/2, 30, GREEN);

if (pause) DrawText("PAUSED", screenWidth/2 - 60, screenHeight/2 - 30, 30, GREEN);

//DRAW THE SCORE IN <player:enemy> format

DrawText(scoreText, screenWidth/2 - 20, screenHeight/2, 10, BLACK);

EndDrawing();
free(scoreText);
}
free(enemyScoreBuffer); free(playerScoreBuffer);
CloseWindow();
return 0;

} 
