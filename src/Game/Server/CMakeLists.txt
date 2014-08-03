set (game_server_SOURCES
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

	ConnectionAdapterSrv.cpp
	GameCycleSrv.cpp
	main.cpp
	NewGameSrv.cpp
)

set (game_server_HEADERS
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

	ConnectionAdapterSrv.h
	GameCycleSrv.h
	NewGameSrv.h
)
qt5_wrap_cpp (game_server_SOURCES ${game_server_HEADERS})

add_executable (GameServer ${game_server_SOURCES})
target_link_libraries (GameServer Core GameCommon ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
