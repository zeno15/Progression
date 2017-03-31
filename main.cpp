#include <cstdlib>
#include <iostream>

#include <Driller/DrillerStart.hpp>
#include <Pong/PongStart.hpp>

#include <Window/Window.hpp>
#include <Window/OpenGL.hpp>
#include <Infrastructure.hpp>
#include <Graphics/Text.hpp>

int main(int _argc, char **_argv) {

	try {
		//Driller::initialiseManagers();

		//Driller::start();

		Pong::initialiseManagers();

		Pong::start();
	}
	catch (std::exception const& _ex) {
		std::cout << "Exception: " << _ex.what() << std::endl;
		getchar();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

	const float width = 1280.0f;
	const float height = 720.0f;
	const std::string resourcePath = "C:/Users/markd/Documents/Git/Progression/resources/";

	Window::VideoMode videoMode;
	videoMode.bitsPerPixel = 32;
	videoMode.width = static_cast<unsigned int>(width);
	videoMode.height = static_cast<unsigned int>(height);
	videoMode.major = 3;
	videoMode.minor = 3;

	Window::Window window = Window::Window(videoMode, "Window Title!", Window::WindowStyle::Default);

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Shading langauge version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	Infrastructure::InstanceCollection::registerInstance<Infrastructure::ShaderManager>();
	if (!Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader("TextShader", resourcePath + "Shaders/TextShader.Vertex.glsl", resourcePath + "Shaders/TextShader.Fragment.glsl")) {
		std::cout << "Failed to load 'TextShader'." << std::endl;
		getchar();
		return EXIT_FAILURE;
	}
	if (!Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader("TextShader").getLocationOfUniforms({ "View", "TexSize", "Colour" })) {
		getchar();
		return EXIT_FAILURE;
	}


	Graphics::Font font;

	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf", 32)) {
		std::cout << "Failed to load file." << std::endl;
		getchar();
		return EXIT_FAILURE;
	}

	Graphics::Text textRender;
	textRender.generateText("'ello poppet", &font);


	auto renderData = Graphics::RenderData();
	renderData.projection = System::Mat4x4::Orthographic2D(0.0f, 1280.0f, 720.0f, 0.0f);
	renderData.view = System::Mat4x4(1.0f);

	bool running = true;
	while (running) {
		System::Event event;
		while (window.pollEvent(event)) {
			if (event.type == System::Event::WindowClosed) {
				running = false;
			}
		}

		window.clear();
		textRender.render(window, renderData);

		window.display();
	}

	return EXIT_SUCCESS;
}