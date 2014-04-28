set (game_SOURCES
	CustomWidgets/MyTaskbar.cpp

	Elements/PlayerMarker.cpp
	Elements/Tile.cpp

	Windows/EquipmentWindow.cpp
	Windows/FightWindow.cpp
	Windows/HealerWindow.cpp
	Windows/MarketWindow.cpp
	Windows/NewGameWindow.cpp
	Windows/PrizeWindow.cpp
	Windows/QuestWindow.cpp
	Windows/RulesWindow.cpp
	Windows/TavernWindow.cpp
	Windows/MarketViewWindow.cpp

	ActionPanel.cpp
	BoardArea.cpp
	MainWindow.cpp
	PlayerWindow.cpp
	
	main.cpp
)

set (game_HEADERS
	Windows/EquipmentWindow.h
	Windows/FightWindow.h
	Windows/HealerWindow.h
	Windows/MarketWindow.h
	Windows/NewGameWindow.h
	Windows/PrizeWindow.h
	Windows/QuestWindow.h
	Windows/TavernWindow.h
	Windows/MarketViewWindow.h

	ActionPanel.h
	BoardArea.h
	MainWindow.h
	PlayerWindow.h
)
qt5_wrap_cpp (game_SOURCES ${game_HEADERS})

add_executable (TheChroniclesOfAndaria ${game_SOURCES})
target_link_libraries (TheChroniclesOfAndaria Core ${Qt5Widgets_LIBRARIES})
