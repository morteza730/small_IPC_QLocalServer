#pragma once

#include <QtCore/QtGlobal>

#if defined(IPC_LIBRARY)
#  define IPC_EXPORT Q_DECL_EXPORT
#else
#  define IPC_EXPORT Q_DECL_IMPORT
#endif
