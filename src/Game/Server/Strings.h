#ifndef STRINGS_H
#define STRINGS_H

namespace Server {
	namespace Errors {
		const QString ListenFail = QObject::tr("Unable to start the server: %1.");
	}

	namespace Logs {
		const QString ClientConnected = QObject::tr("New client connected.");
		const QString ServerIsListening = QObject::tr("Server is listening on port: %1.");
	}
}

#endif // STRINGS_H
