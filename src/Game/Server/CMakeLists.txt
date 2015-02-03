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

	ConnectionAdapterSrv.hpp
	GameCycleSrv.hpp
	NewGameSrv.hpp
)
qt5_wrap_cpp (game_server_SOURCES ${game_server_HEADERS})

add_executable (GameServer ${game_server_SOURCES})
target_link_libraries (GameServer Core GameCommon ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
