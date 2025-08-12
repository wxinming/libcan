#pragma once

#ifdef LIBCAN_NOT_EXPORTS
#define LIBCAN_DLL_EXPORT
#else
//±àÒëÎª¶¯Ì¬Á´½Ó¿â
#ifdef LIBCAN_EXPORTS
#define LIBCAN_DLL_EXPORT __declspec(dllexport)
#pragma warning(disable:4251)
#else
#define LIBCAN_DLL_EXPORT __declspec(dllimport)
#endif // LIBCAN_EXPORTS
#endif // LIBCAN_NOT_EXPORTS

