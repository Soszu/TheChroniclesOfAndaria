set (core_SOURCES
	Containers/Enemy.cpp
	Containers/Equipment.cpp
	Containers/Field.cpp
	Containers/FightParticipant.cpp
	Containers/Item.cpp
	Containers/ItemModel.cpp
	Containers/ItemWearableModel.cpp
	Containers/ItemWearable.cpp
	Containers/Player.cpp
	Containers/Prize.cpp
	Containers/Quest.cpp
	Containers/QuestBook.cpp

# 	Operations/EquipmentManagement.cpp

	Parsers/BoardParser.cpp
	Parsers/EnemyParser.cpp
	Parsers/ItemParser.cpp
	Parsers/PrizeParser.cpp
	Parsers/QuestParser.cpp

	Paths.cpp
	DataManager.cpp
)
set (core_HEADERS
	Containers/ItemModel.h
	Containers/ItemWearableModel.h

)
qt5_wrap_cpp (core_SOURCES ${core_HEADERS})

add_library (Core ${core_SOURCES})
target_link_libraries (Core ${Qt5Widgets_LIBRARIES})
