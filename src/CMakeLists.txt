set (SOURCES
	main.cpp
	gracz.cpp
	mainwindow.cpp
	przedmiot.cpp
	zadanie.cpp
	panelakcji.cpp
	mybutton.cpp
)

set (HEADERS
	gracz.h
	ui_mainwindow.h
	mainwindow.h
	przedmiot.h
	zadanie.h
	panelakcji.h
	mybutton.h
)

set (UI
	mainwindow.ui
)

qt4_wrap_cpp (SOURCES ${HEADERS})
qt4_wrap_ui (SOURCES ${UI})
add_executable (Planszowka
	${SOURCES}
	${HEADERS}
	${UI}
)
target_link_libraries (Planszowka ${QT_LIBRARIES})

