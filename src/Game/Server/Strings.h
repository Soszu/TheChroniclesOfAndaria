#pragma once

namespace Server {
	namespace Errors {
		const QString ListenFail = QObject::tr("Unable to start the server: %1.");
	}

	namespace Logs {
		const QString ClientConnected = QObject::tr("New client connected. (UID: %1)");
		const QString ClientDisconnected = QObject::tr("Client connected. (UID: %1)");
		const QString ServerIsListening = QObject::tr("Server is listening on port: %1.");
	}
}
