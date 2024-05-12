#pragma once
#include "Globals.h"
#include <string>
#include "raylib.h"
#include "ResourceManager.h"

class Text
{
public:
	Text();
	~Text();
	AppStatus Initialise(Resource id, const std::string& file_path, char first_character, int character_size);

	//Method to draw text at a specified position
	void Draw(int x, int y, const std::string& text, const Color& col = WHITE) const;

private:
	// Method to draw a single character at a specified position
	void DrawCharacter(int x, int y, char c, const Color& col = WHITE) const;

	char first_character;	//first character in the bitmap grid
	int character_size;		//size of each character (constant)
	int columns;			//number of columns in the bitmap grid
	int rows;				//number of rows in the bitmap grid

	const Texture2D* img;	//reference to the texture containing the characters
};

