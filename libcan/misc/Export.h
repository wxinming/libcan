#pragma once

#ifdef _DLL
	//±àÒëÎª¶¯Ì¬Á´½Ó¿â
	#ifdef CAN_BUILD_DLL
		#define CAN_DLL_EXPORT __declspec(dllexport)
		#pragma warning(disable:4251)
	#else
		#define CAN_DLL_EXPORT __declspec(dllimport)
	#endif // CAN_BUILD_DLL
#else
	#ifdef _LIB
		#define CAN_DLL_EXPORT
	#else
		#define CAN_DLL_EXPORT
	#endif
#endif // _DLL
