#include <SFML/Graphics.hpp> //Llama a la librería gráfica de SFML.
#include "NodWorld.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "A falling box"); //Creamos una ventana con dimensiones 800x600. 
	window.setFramerateLimit(60);

	sf::Event event; //Creamos un objeto tipo evento, llamado event. 
	sf::Clock clock; //Para llevar el tiempo que toma hacer un frame en el ciclo de window. 

	//Definiendo variables momentaneos.
	bool boolSpace = false;
	bool boolAir = false;
	bool boolD = false;
	bool boolA = false;
	bool boolLShift = false;

	//Creando delta time variable.
	float dt;

	//Configuramos nuestro mundo. 
	World w1;
	w1.setGravity(Vec2(0.0f, 450.0f)); //seteando la gravedad del mundo

	//Seteamos nuestro body. Condiciones inciales.
	Body b1;
	b1.mass = 2.0f;
	b1.invMass = 1 / b1.mass;
	b1.position = Vec2(400.0f, 430.0f); //Posicion inicial
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
	CharacterSprite1.setScale(sf::Vector2f(0.20f, 0.20f));

	//Colocamos el origen del sprite en el centro del sprite. 
	sf::Rect<float> size = CharacterSprite1.getGlobalBounds();
	CharacterSprite1.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));

	//Cargando archivo del floor
	sf::Texture floorTex1;
	sf::Sprite floorSprite1;

	if (!floorTex1.loadFromFile("Assets/Sprites/road1.png"))
	{
		std::cout << "Couldn't load file." << std::endl;
		system("pause");
	}

	//Colocando el floor
	floorSprite1.setTexture(floorTex1);
	floorSprite1.setScale(sf::Vector2f(0.45f, 0.45f));
	floorSprite1.setOrigin(sf::Vector2f(0.0f, -560.0f));


	//Cargando archivo del background
	sf::Texture backgroundTex1;

	if (!backgroundTex1.loadFromFile("Assets/Sprites/City2.png"))
	{
		std::cout << "Couldn't load file." << std::endl;
		system("pause");
	}

	//Colocando el background
	sf::Sprite background;
	background.setTexture(backgroundTex1);
	sf::Rect<float> backSize = background.getGlobalBounds();
	sf::Vector2f targetSize(800.0f, 600.0f);
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
				if (event.key.code == sf::Keyboard::Space)
				{
					boolSpace = true;
					std::cout << "Space pressed!" << std::endl;
				}

				if (event.key.code == sf::Keyboard::D)
				{
					boolD = true;
					std::cout << "D pressed!" << std::endl;
				}

				if (event.key.code == sf::Keyboard::A)
				{
					boolA = true;
					std::cout << "A pressed!" << std::endl;
				}

				if (event.key.code == sf::Keyboard::LShift)
				{
					boolLShift = true;
					std::cout << "LShift pressed!" << std::endl;
				}

			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					boolSpace = false;
					std::cout << "Space released!" << std::endl;
				}

				if (event.key.code == sf::Keyboard::D)
				{
					boolD = false;
					std::cout << "D released!" << std::endl;
				}

				if (event.key.code == sf::Keyboard::A)
				{
					boolA = false;
					std::cout << "A released!" << std::endl;
				}

				if (event.key.code == sf::Keyboard::LShift)
				{
					boolLShift = false;
					std::cout << "LShift released!" << std::endl;
				}
			}

		}

		//teclas para caminar y correr
		if (boolAir == false)
		{
			if ((boolD == true) && (boolLShift == false))
			{
				b1.velocity = Vec2(80.0f, 0.0f);
			}
			else if ((boolD == true) && (boolLShift == true))
			{
				b1.velocity = Vec2(250.0f, 0.0f);
			}
			else if ((boolA == true) && (boolLShift == false))
			{
				b1.velocity = Vec2(-80.0f, 0.0f);
			}
			else if ((boolA == true) && (boolLShift == true))
			{
				b1.velocity = Vec2(-250.0f, 0.0f);
			}
			else if ((boolD == false) && (boolA == false) && (boolAir == false))
			{
				b1.velocity = Vec2(0.0f, 0.0f);
			}
		}

		//teclas de saltar
		if ((boolSpace == true) && (boolAir == false))
		{
			if (boolD == true)
			{
				b1.velocity = Vec2(300.0f, -300.0f);
				boolAir = true;
			}
			else if (boolA == true)
			{
				b1.velocity = Vec2(-300.0f, -300.0f);
				boolAir = true;
			}
			else
			{
				b1.velocity = Vec2(0.0f, -330.0f);
				boolAir = true;
			}
		}

		//Calculo el tiempo que toma hacer un frame.
		sf::Time elapsed = clock.restart();
		dt = elapsed.asSeconds();

		//Uso el tiempo calculado para usar la función Step() de World w1.
		w1.Step(dt);

		//Colision...

		if (b1.position.y >= 430.0f)
		{
			b1.position.y = 430.0f;
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