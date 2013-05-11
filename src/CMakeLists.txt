set (SOURCES
	main.cpp
	gracz.cpp
	mainwindow.cpp
	przedmiot.h
)

set (HEADERS
	gracz.h
	mainwindow.h
	przedmiot.h
)

set (UI
)

qt4_wrap_cpp (SOURCES ${HEADERS})
qt4_wrap_ui (SOURCES ${UI})
add_executable (Planszowka
	${SOURCES}
	${HEADERS}
	${UI}
)
target_link_libraries (Planszowka ${QT_LIBRARIES})

