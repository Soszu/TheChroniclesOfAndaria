include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA)
include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA/elementy)
include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA/okna)
include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA/moje_widzety)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/kontenery)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/operacje)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/parsery)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/sztuczna_inteligencja)

set (SOURCES
	kontenery/ekwipunek.cpp
	kontenery/gracz.cpp
	kontenery/nagroda.cpp
	kontenery/pole.cpp
	kontenery/przeciwnik.cpp
	kontenery/przedmiot.cpp
	kontenery/zadanie.cpp

	operacje/zarzadzanieekwipunkiem.cpp
	operacje/zarzadzaniezadaniami.cpp
	
	parsery/parsernagrod.cpp
	parsery/parserprzeciwnikow.cpp
	parsery/parserprzedmiotow.cpp
	parsery/parserukladu.cpp
	parsery/parserzadan.cpp

	sztuczna_inteligencja/sztucznainteligencja.cpp

	main.cpp
	cyklgry.cpp
	mistrzgry.cpp
	plansza.cpp
)

set (HEADERS
	kontenery/ekwipunek.h
	kontenery/gracz.h
	kontenery/nagroda.h
	kontenery/pole.h
	kontenery/przeciwnik.h
	kontenery/przedmiot.h
	kontenery/zadanie.h

	operacje/zarzadzanieekwipunkiem.h
	operacje/zarzadzaniezadaniami.h
	
	parsery/parsernagrod.h
	parsery/parserprzeciwnikow.h
	parsery/parserprzedmiotow.h
	parsery/parserukladu.h
	parsery/parserzadan.h

	sztuczna_inteligencja/sztucznainteligencja.h

	gra.h
	cyklgry.h
	mistrzgry.h
	plansza.h
)
#add_library( Logic ${SOURCES} ${HEADERS})

add_executable (Planszowka ${SOURCES} ${HEADERS})

target_link_libraries (Planszowka Gui ${QT_LIBRARIES})

