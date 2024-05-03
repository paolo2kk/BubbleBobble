#include "Text.h"
#include "ResourceManager.h"

Text::Text()
{
	first_character = (char)0;
	character_size = 0;
	columns = 0;
	rows = 0;

	img = nullptr;
}
Text::~Text()
{
}
AppStatus Text::Initialise(Resource id, const std::string& file_path, char first_character, int character_size)
{
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(id, file_path) != AppStatus::OK)
	{
		LOG("Failed to load font texture");
		return AppStatus::ERROR;
	}
	img = data.GetTexture(id);
	this->first_character = first_character;
	this->character_size = character_size;

	//Calculate the number of columns and rows in the bitmap grid
	columns = img->width / character_size;
	rows = img->height / character_size;

	return AppStatus::OK;
}
void Text::Draw(int x, int y, const std::string& text, const Color& col) const
{
	//Initialize the horizontal offset to the starting x-coordinate
	int offset_x = x;

	//Iterate through each character in the text string
	for (int i = 0; i < text.length(); ++i)
	{
		//Draw the current character at the current position with the specified color
		DrawCharacter(offset_x, y, text[i], col);

		//Update the horizontal offset to position the next character
		//Distance between each character is equal to the character size
		offset_x += character_size;
	}
}
void Text::DrawCharacter(int x, int y, char c, const Color& col) const
{
	int char_index, coord_x, coord_y, pixel_x, pixel_y;

	//Calculate the character index based on the first character
	char_index = c - first_character;

	//Calculate the coordinates of the character in the texture grid
	coord_x = char_index % columns;
	coord_y = char_index / columns;

	//Check if the calculated coordinates are out of bounds
	if (coord_x < 0 || coord_x >= columns || coord_y < 0 || coord_y >= rows)
	{
		LOG("Internal error, character index invalid when drawing text: (%d,%d)", coord_x, coord_y);
		return;
	}

	//Calculate the pixel coordinates of the character in the texture
	pixel_x = coord_x * character_size;
	pixel_y = coord_y * character_size;

	//Define a rectangle representing the character in the texture
	Rectangle rc = { (float)pixel_x, (float)pixel_y, (float)character_size, (float)character_size };

	//Draw the character
	DrawTextureRec(*img, rc, { (float)x, (float)y }, col);
}