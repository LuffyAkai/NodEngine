#include <SFML/Graphics.hpp> //Llama a la librería gráfica de SFML.
#include "NodWorld.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "A falling box"); //Creamos una ventana con dimensiones 800x600. 
	window.setFramerateLimit(60);

	sf::Event event; //Creamos un objeto tipo evento, llamado event. 
	sf::Clock clock; //Para llevar el tiempo que toma hacer un frame en el ciclo de window. 

	bool gliding = false;

	//Definiendo variables momentaneos.
	bool boolAir = false;
	bool boolD = false;
	bool boolA = false;

	//Creando delta time variable.
	float dt;

	//Configuramos nuestro mundo. 
	World w1;
	w1.setGravity(Vec2(0.0f, 150.0f)); //seteando la gravedad del mundo

	//Seteamos nuestro body. Condiciones inciales.
	Body b1;
	b1.force = Vec2(0.0f, 0.0f);
	b1.mass = 2.0f;
	b1.invMass = 1 / b1.mass;
	b1.position = Vec2(0.0f, 50.0f); //Posicion inicial
	b1.velocity = Vec2(0.0f, 0.0f); //Velocidad inicial


	w1.addBody(&b1);

	//Cargando Character. 
	sf::Texture CharacterTex1;
	sf::Sprite CharacterSprite1;

	if (!CharacterTex1.loadFromFile("Assets/Sprites/fallen1.png"))
	{
		std::cout << "Could not load texture. . ." << std::endl;
		system("pause");
	}

	//Configurando sprites.

	CharacterSprite1.setTexture(CharacterTex1);
	CharacterSprite1.setScale(sf::Vector2f(0.15f, 0.15f));

	//Colocamos el origen del sprite en el centro del sprite. 
	sf::Rect<float> size = CharacterSprite1.getGlobalBounds();
	CharacterSprite1.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));

	//Cargando archivo del floor
	sf::Texture floorTex1;
	sf::Sprite floorSprite1;

	if (!floorTex1.loadFromFile("Assets/Sprites/Pad3.png"))
	{
		std::cout << "Couldn't load file." << std::endl;
		system("pause");
	}

	//Colocando el floor
	floorSprite1.setTexture(floorTex1);
	floorSprite1.setScale(sf::Vector2f(0.45f, 0.45f));
	//floorSprite1.setTextureRect(sf::IntRect(50, 50, 30, 30));
	floorSprite1.setOrigin(sf::Vector2f(0.0f, 350.0f));

	//Cargando archivo del background
	sf::Texture backgroundTex1;

	if (!backgroundTex1.loadFromFile("Assets/Sprites/sky_2.png"))
	{
		std::cout << "Couldn't load file." << std::endl;
		system("pause");
	}

	//Colocando el background
	sf::Sprite background;
	background.setTexture(backgroundTex1);
	sf::Rect<float> backSize = background.getGlobalBounds();
	sf::Vector2f targetSize(1280.0f, 1024.0f);
	background.setScale(targetSize.x / backSize.width, targetSize.y / backSize.height);




	//Para ilustrar lo que queremos... colocaremos el personaje en el centro de la pantalla.
	//El sprite usa la misma posición inicial que se le da al cuerpo en la configuración de cuerpo.
	CharacterSprite1.setPosition(sf::Vector2f(b1.position.x, b1.position.y));
	floorSprite1.setPosition(sf::Vector2f(0.0f, 300.0f));

	//Lo que sucede en la pantalla...
	while (window.isOpen()) //Se mantiene el ciclo while mientras la ventana esté abierta. 
	{
		while (window.pollEvent(event)) //Lee si hubo alguna señal de entrada (mouse, teclado, joystick...) 
		{
			if (event.type == sf::Event::Closed) //Si el usuario presiona X (para salir de la ventana)...
			{
				window.close(); //... Cierra la ventana
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					gliding = true;
					std::cout << "P Pressed!" << std::endl;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					gliding = false;
					std::cout << "P released!" << std::endl;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (gliding == true)
			{
				b1.addForce(Vec2(100.0f, 0.0f));
			}
			else
			{
				b1.addForce(Vec2(700.0f, 0.0f));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (gliding == true)
			{
				b1.addForce(Vec2(-100.0f, 0.0f));
			}
			else
			{
				b1.addForce(Vec2(-700.0f, 0.0f));
			}
		}

		if (gliding == true)
		{
			b1.force.y = (-430.0f);
			b1.velocity.y = (150.0f);
			boolAir = false;
			std::cout << "fueza activada" << std::endl;
		}
		else
		{
			b1.force.y = (50.0f);
			boolAir = false;
		}

		//Calculo el tiempo que toma hacer un frame.
		sf::Time elapsed = clock.restart();
		dt = elapsed.asSeconds();

		//Uso el tiempo calculado para usar la función Step() de World w1.
		w1.Step(dt);

		if ((b1.position.y >= 50.0f) && (b1.position.y < 100.0f) && (b1.position.x <= 140.0f))
		{
			b1.position.y = 50.0f;
			boolAir = false;
		}

		CharacterSprite1.setPosition(sf::Vector2f(b1.position.x, b1.position.y));

		//Windows rendering
		window.clear(sf::Color::Black);
		window.draw(background);
		window.draw(floorSprite1);
		window.draw(CharacterSprite1);
		window.display();
	}
	return 0;
}