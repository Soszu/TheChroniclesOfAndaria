set (Editor_SRCS
	main.cpp
	MainWindow.cpp

	CustomWidgets/EffectsListEdit.cpp
	CustomWidgets/EnumEdit.cpp
	CustomWidgets/PrizeEdit.cpp

	Editors/BoardEditor.cpp
	Editors/EnemiesEditor.cpp
	Editors/ItemsEditor.cpp
	Editors/QuestEditor.cpp
)

set (Editor_HDRS
	MainWindow.hpp

	CustomWidgets/EffectsListEdit.hpp
	CustomWidgets/EnumEdit.hpp
	CustomWidgets/PrizeEdit.hpp

	Editors/EnemiesEditor.hpp
	Editors/ItemsEditor.hpp
	Editors/QuestEditor.hpp
)

qt5_wrap_cpp (Editor_SRCS ${Editor_HDRS})

add_executable (Editor ${Editor_SRCS})
target_link_libraries (Editor Core ${Qt5Widgets_LIBRARIES})
