set (Editor_SRCS
	main.cpp
	MainWindow.cpp

	CustomWidgets/EffectEdit.cpp
	CustomWidgets/EffectsEdit.cpp
	CustomWidgets/EnumEdit.cpp
	CustomWidgets/PrizeEdit.cpp
	CustomWidgets/ObjectiveEdit.cpp
	CustomWidgets/ObjectivesEdit.cpp
	CustomWidgets/ListEdit.cpp

	CustomWidgets/Tools/Tool.cpp
	CustomWidgets/Tools/BoardSizeTool.cpp
	CustomWidgets/Tools/TerrainsTool.cpp
	CustomWidgets/Tools/RulingTool.cpp
	CustomWidgets/Tools/InitialPositionsTool.cpp

	Editors/BoardEditor.cpp
	Editors/EnemiesEditor.cpp
	Editors/ItemsEditor.cpp
	Editors/QuestEditor.cpp
)

set (Editor_HDRS
	MainWindow.hpp

	CustomWidgets/EffectEdit.hpp
	CustomWidgets/EffectsEdit.hpp
	CustomWidgets/EnumEdit.hpp
	CustomWidgets/PrizeEdit.hpp
	CustomWidgets/ObjectiveEdit.hpp
	CustomWidgets/ObjectivesEdit.hpp
	CustomWidgets/ListEdit.hpp

	Editors/BoardEditor.hpp
	Editors/EnemiesEditor.hpp
	Editors/ItemsEditor.hpp
	Editors/QuestEditor.hpp

	CustomWidgets/Tools/Tool.hpp
	CustomWidgets/Tools/BoardSizeTool.hpp
# 	CustomWidgets/Tools/TerrainsTool.hpp
# 	CustomWidgets/Tools/RulingTool.hpp
# 	CustomWidgets/Tools/InitialPositionsTool.hpp
)

qt5_wrap_cpp (Editor_SRCS ${Editor_HDRS})

add_executable (Editor ${Editor_SRCS})
target_link_libraries (Editor Core Resources ${Qt5Widgets_LIBRARIES})
