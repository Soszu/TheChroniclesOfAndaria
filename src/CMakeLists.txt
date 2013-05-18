set (SOURCES
	main.cpp
	mainwindow.cpp
	oknonowejgry.cpp
	cyklgry.cpp
	mistrzgry.cpp
	plansza.cpp
	panelakcji.cpp
	oknogracza.cpp
	mojpasek.cpp
	oknoekwipunek.cpp
	oknozadania.cpp
	obszarplanszy.cpp
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
	mainwindow.h
	oknonowejgry.h
	cyklgry.h
	mistrzgry.h
	plansza.h
	panelakcji.h
	oknogracza.h
	mojpasek.h
	oknoekwipunek.h
	oknozadania.h
	obszarplanszy.h
	mybutton.h
	gracz.h
	przedmiot.h
	zadanie.h
	ekwipunek.h
	nagroda.h
	przeciwnik.h
)


set (RESOURCES
	zasoby.qrc
)

qt4_wrap_cpp (SOURCES ${HEADERS})
qt4_add_resources (RESOURCES_RCC ${RESOURCES})
add_executable (Planszowka
	${SOURCES}
	${RESOURCES_RCC}
	${HEADERS}
)
target_link_libraries (Planszowka ${QT_LIBRARIES})
