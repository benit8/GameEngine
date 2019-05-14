##
## EPITECH PROJECT, 2019
## GameEngine
## File description:
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GameEngine VERSION 0.1.0)
add_executable(exe)

target_compile_features(exe PRIVATE cxx_std_17)

target_compile_options(exe PUBLIC -fPIC)
target_compile_options(exe PRIVATE -W -Wall -Wextra)
target_compile_options(exe PRIVATE -g3)

target_include_directories(exe
PUBLIC
	engine
	extern
PRIVATE
	tests
)

target_sources(exe
PUBLIC
	./engine/Application.cpp
	./engine/Application.hpp
	./engine/EventDispatcher.cpp
	./engine/EventDispatcher.hpp
	./engine/Logger.cpp
	./engine/Logger.hpp
	./engine/StateManager.cpp
	./engine/StateManager.hpp
	./engine/EventListeners/Close.hpp
	./engine/EventListeners/Focus.hpp
	./engine/EventListeners/IEventListener.hpp
	./engine/EventListeners/Key.hpp
	./engine/EventListeners/MouseButton.hpp
	./engine/EventListeners/MouseFocus.hpp
	./engine/EventListeners/MouseMove.hpp
	./engine/EventListeners/MouseWheel.hpp
	./engine/EventListeners/Resize.hpp
	./engine/EventListeners/Text.hpp
	./engine/GUI/Background.cpp
	./engine/GUI/Background.hpp
#	./engine/GUI/Box.cpp
#	./engine/GUI/Box.hpp
	./engine/GUI/Button.cpp
	./engine/GUI/Button.hpp
	./engine/GUI/Env.cpp
	./engine/GUI/Env.hpp
	./engine/GUI/GUI.hpp
	./engine/GUI/Input.cpp
	./engine/GUI/Input.hpp
#	./engine/GUI/MessageBox.cpp
#	./engine/GUI/MessageBox.hpp
#	./engine/GUI/Modal.cpp
#	./engine/GUI/Modal.hpp
	./engine/GUI/Parent.cpp
	./engine/GUI/Parent.hpp
	./engine/GUI/Root.cpp
	./engine/GUI/Root.hpp
	./engine/GUI/Widget.cpp
	./engine/GUI/Widget.hpp
	./engine/Graphics/AnimatedSprite.cpp
	./engine/Graphics/AnimatedSprite.hpp
	./engine/Graphics/Animation.cpp
	./engine/Graphics/Animation.hpp
	./engine/Graphics/FPSCounter.cpp
	./engine/Graphics/FPSCounter.hpp
	./engine/Graphics/FontLoader.cpp
	./engine/Graphics/FontLoader.hpp
	./engine/Graphics/GIF.cpp
	./engine/Graphics/GIF.hpp
	./engine/Graphics/Window.cpp
	./engine/Graphics/Window.hpp
	./engine/States/State.cpp
	./engine/States/State.hpp
	./engine/Utils/Signal.hpp
	./engine/Utils/Singleton.hpp

PUBLIC
	./extern/imgui/imconfig.h
	./extern/imgui/imgui-SFML.cpp
	./extern/imgui/imgui-SFML.h
	./extern/imgui/imgui.cpp
	./extern/imgui/imgui.h
	./extern/imgui/imgui_demo.cpp
	./extern/imgui/imgui_draw.cpp
	./extern/imgui/imgui_internal.h
	./extern/imgui/imgui_widgets.cpp
	./extern/imgui/imstb_rectpack.h
	./extern/imgui/imstb_textedit.h
	./extern/imgui/imstb_truetype.h
	./extern/json/json.hpp
	./extern/stb/stb_gif.h
	./extern/stb/stb_image.cpp
	./extern/stb/stb_image.h
	./extern/tinyformat/tinyformat.hpp

PRIVATE
	./tests/main.cpp
	./tests/States/Test.hpp
)

target_link_libraries(exe
PUBLIC
	GL
	sfml-system
	sfml-window
	sfml-graphics
)