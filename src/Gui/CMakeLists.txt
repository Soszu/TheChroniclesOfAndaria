set (gui_SOURCES
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
)

set (gui_HEADERS
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

qt5_wrap_cpp (gui_SOURCES ${gui_HEADERS})
add_library (Gui ${gui_SOURCES})
target_link_libraries (Gui ${Qt5Widgets_LIBRARIES})
