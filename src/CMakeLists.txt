set (SOURCES
	main.cpp
	mainwindow.cpp
	panelakcji.cpp
	mybutton.cpp
	gracz.cpp
	ekwipunek.cpp
	nagroda.cpp
	przedmiot.cpp
	zadanie.cpp
	przeciwnik.cpp
)

set (HEADERS
	gra.h
	ui_mainwindow.h
	mainwindow.h
	panelakcji.h
	mybutton.h
	gracz.h
	przedmiot.h
	zadanie.h
	ekwipunek.h
	nagroda.h
	przeciwnik.h
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

