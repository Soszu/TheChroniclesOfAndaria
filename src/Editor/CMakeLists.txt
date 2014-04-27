set (Editor_SRCS
	main.cpp
	MainWindow.cpp
	ContentEditor.cpp
)

set (Editor_HDRS
	MainWindow.h
	ContentEditor.h
	Strings.h
	Shortcuts.h
)

qt5_wrap_cpp (Editor_SRCS ${Editor_HDRS})

add_executable (Editor ${Editor_SRCS})
target_link_libraries (Editor Core ${Qt5Widgets_LIBRARIES})
