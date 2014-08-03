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
#	Windows/EquipmentWindow.h
#	Windows/FightWindow.h
#	Windows/HealerWindow.h
#	Windows/MarketWindow.h
#	Windows/NewGameWindow.h
#	Windows/PrizeWindow.h
#	Windows/QuestWindow.h
#	Windows/TavernWindow.h
#	Windows/MarketViewWindow.h

#	Handlers/HandlerTemplate.h

#	FixedComponents/ActionPanel.h
#	FixedComponents/BoardArea.h
#	FixedComponents/PlayerWindow.h

	ConnectionAdapterClt.h
	GameCycleClt.h
	MainWindow.h
	NewGameClt.h
	NewGameGui.h
)
qt5_wrap_cpp (game_client_SOURCES ${game_client_HEADERS})

add_executable (GameClient ${game_client_SOURCES})
target_link_libraries (GameClient Core GameCommon ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
