class Character
{
private:
	float characterPosX;
	float characterPosY;
	float characterDirectionX;
	float characterDirectionY;
	sf::Texture texture;
	sf::Sprite sprite;
//protected:

public:

	Character();
	void draw(sf::RenderWindow* window);
	void draw();
	void updatePosition();
	void characterMovement(sf::Event e);
};
