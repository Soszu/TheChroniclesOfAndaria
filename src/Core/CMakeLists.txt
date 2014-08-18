set (core_SOURCES

	Containers/Effect.cpp
	Containers/Enemy.cpp
	Containers/Entity.cpp
	Containers/Equipment.cpp
	Containers/Field.cpp
	Containers/Item.cpp
	Containers/Journal.cpp
	Containers/Player.cpp
	Containers/PlayerDraft.cpp
	Containers/Prize.cpp
	Containers/Quest.cpp

	Containers/Bases/EnemyBase.cpp
	Containers/Bases/ItemBase.cpp
	Containers/Bases/QuestBase.cpp

	Containers/Models/ItemModel.cpp

#	Parsers/BoardParser.cpp
#	Parsers/EnemyParser.cpp
#	Parsers/PrizeParser.cpp
#	Parsers/QuestParser.cpp

	Paths.cpp
	DataManager.cpp
	DataKeeper.cpp
)
set (core_HEADERS
)
qt5_wrap_cpp (core_SOURCES ${core_HEADERS})

add_library (Core ${core_SOURCES})
target_link_libraries (Core ${Qt5Widgets_LIBRARIES})
