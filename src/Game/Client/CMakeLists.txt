set (game_client_SOURCES
#	CustomWidgets/MyTaskbar.cpp

#	Elements/PlayerMarker.cpp
#	Elements/Tile.cpp

#	Windows/EquipmentWindow.cpp
#	Windows/FightWindow.cpp
#	Windows/HealerWindow.cpp
#	Windows/MarketWindow.cpp
#	Windows/NewGameWindow.cpp
#	Windows/PrizeWindow.cpp
#	Windows/QuestWindow.cpp
#	Windows/RulesWindow.cpp
#	Windows/TavernWindow.cpp
#	Windows/MarketViewWindow.cpp

#	Handlers/HandlerTemplate.cpp
#	Handlers/HealerHandler.cpp
#	Handlers/MarketHandler.cpp
#	Handlers/MonsterFightHandler.cpp
#	Handlers/PVPHandler.cpp
#	Handlers/TavernHandler.cpp

#	FixedComponents/ActionPanel.cpp
#	FixedComponents/BoardArea.cpp
#	FixedComponents/PlayerWindow.cpp

#	Board.cpp
#	GameMaster.cpp

	ConnectionAdapterClt.cpp
	GameCycleClt.cpp
	main.cpp
	MainWindow.cpp
	NewGameClt.cpp
	NewGameGui.cpp
)

set (game_client_HEADERS
#	Windows/EquipmentWindow.hpp
#	Windows/FightWindow.hpp
#	Windows/HealerWindow.hpp
#	Windows/MarketWindow.hpp
#	Windows/NewGameWindow.hpp
#	Windows/PrizeWindow.hpp
#	Windows/QuestWindow.hpp
#	Windows/TavernWindow.hpp
#	Windows/MarketViewWindow.hpp

#	Handlers/HandlerTemplate.hpp

#	FixedComponents/ActionPanel.hpp
#	FixedComponents/BoardArea.hpp
#	FixedComponents/PlayerWindow.hpp

	ConnectionAdapterClt.hpp
	GameCycleClt.hpp
	MainWindow.hpp
	NewGameClt.hpp
	NewGameGui.hpp
)
qt5_wrap_cpp (game_client_SOURCES ${game_client_HEADERS})

add_executable (GameClient ${game_client_SOURCES})
target_link_libraries (GameClient Core GameCommon ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
