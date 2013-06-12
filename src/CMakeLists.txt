set (SOURCES
	main.cpp
	mainwindow.cpp
	oknonowejgry.cpp
	cyklgry.cpp
	mistrzgry.cpp
	plansza.cpp
	parserukladu.cpp
	parserprzeciwnikow.cpp
	parserprzedmiotow.cpp
	parsernagrod.cpp
	panelakcji.cpp
	oknogracza.cpp
	mojpasek.cpp
	zarzadzanieekwipunkiem.cpp
	oknoekwipunek.cpp
	oknobazaru.cpp
	oknozadania.cpp
	obszarplanszy.cpp
	hex.cpp
	pionek.cpp
	mojprzycisk.cpp
	gracz.cpp
	ekwipunek.cpp
	nagroda.cpp
	przedmiot.cpp
	zadanie.cpp
	przeciwnik.cpp
	pole.cpp
	walka.cpp
	oknonagrody.cpp
)

set (HEADERS
	gra.h
	mainwindow.h
	oknonowejgry.h
	cyklgry.h
	mistrzgry.h
	plansza.h
	parserukladu.h
	parserprzeciwnikow.h
	parserprzedmiotow.h
	parsernagrod.h
	panelakcji.h
	oknogracza.h
	mojpasek.h
	zarzadzanieekwipunkiem.h
	oknoekwipunek.h
	oknobazaru.h
	oknozadania.h
	obszarplanszy.h
	hex.h
	pionek.h
	mojprzycisk.h
	gracz.h
	przedmiot.h
	zadanie.h
	ekwipunek.h
	nagroda.h
	przeciwnik.h
	pole.h
	walka.h
	oknonagrody.h
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
