/*   All Rights Reserved.                                   */

#ifndef __FW_CELLSYSTEMCALLBACK_H__
#define __FW_CELLSYSTEMCALLBACK_H__

#include <sysutil/sysutil_common.h>

class FWCellSystemCallback {
public:
	static void registerUserCallback(CellSysutilCallback callback)
		{
			mpUserCallback = callback;
		}

	static void userCallback(const uint64_t status, const uint64_t param,
							 void *userdata)
		{
			if (mpUserCallback != 0) {
				mpUserCallback(status, param, userdata);
			}
		}

private:
	static CellSysutilCallback mpUserCallback;
};

#endif // __FW_CELLSYSTEMCALLBACK_H__
