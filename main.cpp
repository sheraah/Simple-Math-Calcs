#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

#define PI 3.14159265
#define MoveSpeed 0.1f

sf::RenderWindow window({ 1500,1000 }, "MathTest", sf::Style::Close);
sf::Event evnt;

float RadToDeg(const float& Rad)
{
	return (180.f * Rad / PI);
}

float CalcTanAngle(const float& GegenKathete, const float& AnKathete)
{
	return RadToDeg(atan(GegenKathete / AnKathete));
}

const float& CalcRotationAngle(const sf::Vector2f& From, const sf::Vector2f& To, const float& CurrRotaion)
{
	sf::Vector2f Dist = To - From;

	int Side = 0;
	if (To.x >= From.x && To.y <= From.y) Side = 0;
	if (To.x >= From.x && To.y >= From.y) Side = 1;
	if (To.x <= From.x && To.y >= From.y) Side = 2;
	if (To.x <= From.x && To.y <= From.y) Side = 3;

	float angle = (Side == 0 || Side == 2) ? abs(CalcTanAngle(Dist.x, Dist.y)) : abs(CalcTanAngle(Dist.y, Dist.x));

	return 90.f * Side + angle - CurrRotaion;
}

int main()
{
	srand(unsigned int(time(0)));

	sf::RectangleShape Shape({100,100});
	Shape.setPosition({ 100, 450 });
	Shape.setOrigin({ Shape.getSize().x / 2, Shape.getSize().y / 2});

	sf::RectangleShape Shape2({ 100,100 });
	Shape2.setPosition({ 600, 450 });
	Shape2.setOrigin({ Shape2.getSize().x / 2, Shape2.getSize().y / 2 });

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case  sf::Event::Closed:
				window.close();
				break;
			}
		}




		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Shape.move({ 0.f,-MoveSpeed });
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Shape.move({ 0.f,MoveSpeed });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Shape.move({ -MoveSpeed, 0.f });
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Shape.move({ MoveSpeed, 0.f });

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Shape2.move({ 0.f,-MoveSpeed });
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Shape2.move({ 0.f,MoveSpeed });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Shape2.move({ -MoveSpeed, 0.f });
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Shape2.move({ MoveSpeed, 0.f });

		Shape.rotate(CalcRotationAngle(Shape.getPosition(), Shape2.getPosition(), Shape.getRotation()));
		Shape2.rotate(CalcRotationAngle(Shape2.getPosition(), Shape.getPosition(), Shape2.getRotation()));

		window.clear();

		window.draw(Shape);
		window.draw(Shape2);

		window.display();
	}
}