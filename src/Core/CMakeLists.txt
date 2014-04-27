set (core_SOURCES
	AI/AI.cpp

	Containers/Enemy.cpp
	Containers/Equipment.cpp
	Containers/Field.cpp
	Containers/Item.cpp
	Containers/Player.cpp
	Containers/Prize.cpp
	Containers/Quest.cpp

	Operations/EquipmentManagement.cpp
	Operations/QuestManagement.cpp

	Parsers/BoardParser.cpp
	Parsers/EnemyParser.cpp
	Parsers/ItemParser.cpp
	Parsers/PrizeParser.cpp
	Parsers/QuestParser.cpp

	Paths.cpp
	DataManager.cpp

	Board.cpp
	GameCycle.cpp
	GameMaster.cpp
)
#set (core_HEADERS
#	
#)
#qt5_wrap_cpp (core_SOURCES ${core_HEADERS})

add_library (Core ${core_SOURCES})
target_link_libraries (Core ${Qt5Widgets_LIBRARIES})
