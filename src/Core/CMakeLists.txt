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

	Board.cpp
	GameCycle.cpp
	GameMaster.cpp

	main.cpp
)

add_executable (KronikiAndarii ${core_SOURCES})
target_link_libraries (KronikiAndarii Gui ${Qt5Widgets_LIBRARIES})
