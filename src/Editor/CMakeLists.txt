set (Editor_SRCS
	main.cpp
	MainWindow.cpp

	CustomWidgets/EffectsListEdit.cpp
	CustomWidgets/EnumEdit.cpp
	CustomWidgets/PrizeEdit.cpp

	Editors/EnemiesEditor.cpp
	Editors/ItemsEditor.cpp
)

set (Editor_HDRS
	MainWindow.h

	CustomWidgets/EffectsListEdit.h
	CustomWidgets/EnumEdit.h
	CustomWidgets/PrizeEdit.hpp

	Editors/EnemiesEditor.h
	Editors/ItemsEditor.h
)

qt5_wrap_cpp (Editor_SRCS ${Editor_HDRS})

add_executable (Editor ${Editor_SRCS})
target_link_libraries (Editor Core ${Qt5Widgets_LIBRARIES})
