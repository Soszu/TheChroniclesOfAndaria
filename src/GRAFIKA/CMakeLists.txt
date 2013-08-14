include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA)
include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA/elementy)
include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA/okna)
include_directories (${Planszowka_SOURCE_DIR}/src/GRAFIKA/moje_widzety)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/kontenery)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/operacje)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/parsery)
include_directories (${Planszowka_SOURCE_DIR}/src/LOGIKA/sztuczna_inteligencja)


set (items_SOURCES
	elementy/hex.cpp
	elementy/pionek.cpp
)

set (items_HEADERS
	elementy/hex.h
	elementy/pionek.h
)

set (gui_SOURCES
	moje_widzety/mojpasek.cpp
	moje_widzety/mojprzycisk.cpp
	
	okna/oknobazaru.cpp
	okna/oknoekwipunek.cpp
	okna/oknonagrody.cpp
	okna/oknonowejgry.cpp
	okna/oknotawerny.cpp
	okna/oknozadania.cpp
	okna/oknozasad.cpp
	okna/walka.cpp

	mainwindow.cpp
	obszarplanszy.cpp
	oknogracza.cpp
	panelakcji.cpp
)

set (gui_HEADERS
	moje_widzety/mojpasek.h
	moje_widzety/mojprzycisk.h

	okna/oknobazaru.h
	okna/oknoekwipunek.h
	okna/oknonagrody.h
	okna/oknonowejgry.h
	okna/oknotawerny.h
	okna/oknozadania.h
	okna/oknozasad.h
	okna/walka.h

	mainwindow.h
	obszarplanszy.h
	oknogracza.h
	panelakcji.h
)

qt4_wrap_cpp (gui_SOURCES ${gui_HEADERS})

add_library (Gui ${items_SOURCES} ${gui_SOURCES} ${items_HEADERS} ${gui_HEADERS})

