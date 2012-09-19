class Character
{
private:
	float characterPosX;
	float characterPosY;
	sf::Texture texture;
	sf::Sprite sprite;
//protected:

public:

	Character();
	void draw(sf::RenderWindow* window);
	void draw();
	void characterMovementLeft();
	void characterMovementRight();
	void characterMovementUp();
	void characterMovementDown();
	void updatePosition();
};
