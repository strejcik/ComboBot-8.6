// pch.h: wstępnie skompilowany plik nagłówka.
// Wymienione poniżej pliki są kompilowane tylko raz, co poprawia wydajność kompilacji dla przyszłych kompilacji.
// Ma to także wpływ na wydajność funkcji IntelliSense, w tym uzupełnianie kodu i wiele funkcji przeglądania kodu.
// Jednak WSZYSTKIE wymienione tutaj pliki będą ponownie kompilowane, jeśli którykolwiek z nich zostanie zaktualizowany między kompilacjami.
// Nie dodawaj tutaj plików, które będziesz często aktualizować (obniża to korzystny wpływ na wydajność).

#ifndef PCH_H
#define PCH_H

// w tym miejscu dodaj nagłówki, które mają być wstępnie kompilowane
#include "framework.h"
#include <timeapi.h>
#include <io.h>
#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <boost/asio.hpp>
#include <WS2tcpip.h>
#include <limits>
#include "Util.h"
#include "Singleton.h"
#include "Menu.h"
#include "Structs.h"
#include "Mem.h"
#include "MemReader.h"
#include "ComboRune.h"
#include "PacketSend.h"


#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <deque>

#include "Message.h"
#include "BoostLineClient.h"


#pragma comment(lib, "winmm.lib")
#endif //PCH_H
