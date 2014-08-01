set (game_common_SOURCES
	DataKeeper.cpp
	Message.cpp
	ConnectionAdapter.cpp
)

set (game_common_HEADERS
	ConnectionAdapter.h
	DataKeeper.h
	Message.h
)
qt5_wrap_cpp (game_common_SOURCES ${game_common_HEADERS})

add_library (GameCommon ${game_common_SOURCES})
target_link_libraries (GameCommon Core ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
