#pragma once

#include <QtCore/qglobal.h>

#if defined(IPC_LIBRARY)
#  define IPC_EXPORT Q_DECL_EXPORT
#else
#  define IPC_EXPORT Q_DECL_IMPORT
#endif
