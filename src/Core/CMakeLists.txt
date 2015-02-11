set (core_SOURCES

	Paths.cpp
	Enums.cpp
	DataManager.cpp
	Mod.cpp

	Containers/Coordinates.cpp
	Containers/Effect.cpp
	Containers/Enemy.cpp
	Containers/Entity.cpp
	Containers/Equipment.cpp
	Containers/Item.cpp
	Containers/Journal.cpp
	Containers/Player.cpp
	Containers/PlayerDraft.cpp
	Containers/Prize.cpp
	Containers/Quest.cpp
	Containers/Terrain.cpp
	Containers/Test.cpp

	Containers/Bases/EnemyBase.cpp
	Containers/Bases/ItemBase.cpp
	Containers/Bases/QuestBase.cpp

	Containers/Models/BoardModel.cpp
	Containers/Models/EnemyModel.cpp
	Containers/Models/ItemModel.cpp
	Containers/Models/QuestModel.cpp

	Parsers/BoardParser.cpp
	Parsers/EnemyParser.cpp
	Parsers/PrizeParser.cpp
	Parsers/ItemParser.cpp
#	Parsers/QuestParser.cpp

	Widgets/Map.cpp
	Widgets/Tile.cpp
)

set (core_HEADERS
	Widgets/Map.hpp

	Containers/Models/BoardModel.hpp
)

qt5_wrap_cpp (core_SOURCES ${core_HEADERS})

add_library (Core ${core_SOURCES})
target_link_libraries (Core ${Qt5Widgets_LIBRARIES})
