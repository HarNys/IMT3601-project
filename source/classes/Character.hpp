class Character
{
private:
	int characterPosX;
	int characterPosY;
	sf::Texture texture;
	sf::Sprite sprite;
//protected:

public:

	Character();
	void draw(sf::RenderWindow* window);
};