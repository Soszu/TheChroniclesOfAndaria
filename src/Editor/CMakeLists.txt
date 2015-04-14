set (Editor_SRCS
	main.cpp
	MainWindow.cpp

	CustomWidgets/EffectsListEdit.cpp
	CustomWidgets/EnumEdit.cpp
	CustomWidgets/PrizeEdit.cpp
	CustomWidgets/ObjectiveEdit.cpp
	CustomWidgets/ObjectivesEdit.cpp
	CustomWidgets/ListEdit.cpp

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
	CustomWidgets/ObjectiveEdit.hpp
	CustomWidgets/ObjectivesEdit.hpp
	CustomWidgets/ListEdit.hpp

	Editors/BoardEditor.hpp
	Editors/EnemiesEditor.hpp
	Editors/ItemsEditor.hpp
	Editors/QuestEditor.hpp
)

qt5_wrap_cpp (Editor_SRCS ${Editor_HDRS})

add_executable (Editor ${Editor_SRCS})
target_link_libraries (Editor Core Resources ${Qt5Widgets_LIBRARIES})
