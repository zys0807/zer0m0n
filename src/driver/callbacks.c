////////////////////////////////////////////////////////////////////////////
//
//	zer0m0n DRIVER
//
//  Copyright 2013 Conix Security, Nicolas Correia, Adrien Chevalier
//
//  This file is part of zer0m0n.
//
//  Zer0m0n is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Zer0m0n is distibuted in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Zer0m0n.  If not, see <http://www.gnu.org/licenses/>.
//
//
//	File :		callbacks.c
//	Abstract :	Callbacks handlers.
//	Revision : 	v1.0
//	Author :	Adrien Chevalier & Nicolas Correia
//	Email :		adrien.chevalier@conix.fr nicolas.correia@conix.fr
//	Date :		2013-12-26	  
//	Notes : 	
//
/////////////////////////////////////////////////////////////////////////////
#include "callbacks.h"
#include "monitor.h"
#include "main.h"
#include "comm.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Description :
//		Image load callback. Allows being notified when a PE image is loaded into kernel space.
//	Parameters :
//		See http://msdn.microsoft.com/en-us/library/windows/hardware/ff559957(v=vs.85).aspx
//	Return value :
//		None
//	Process :
//		The function tests if the image is mapped into kernel memory (ImageInfo->SystemModeImage is set),
//		only if the analysis has started (if monitored_process_list is not NULL). If so, the image load
//		is logged, along with its filename (DriverName->name).
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
VOID imageCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{	
	NTSTATUS status;
	PWCHAR parameter = NULL;
	ULONG currentProcessId;

	if(ImageInfo)
	{
		currentProcessId = (ULONG)PsGetCurrentProcessId();
		
		if(monitored_process_list && ImageInfo->SystemModeImage)
		{
			parameter = ExAllocatePoolWithTag(NonPagedPool, (MAXSIZE+1)*sizeof(WCHAR), BUF_POOL_TAG);
			if(parameter && NT_SUCCESS(RtlStringCchPrintfW(parameter, MAXSIZE, L"1,0,s,DriverName->%wZ", FullImageName)))
			{
				sendLogs(currentProcessId,L"LOAD_DRIVER", parameter);
				cleanMonitoredProcessList();
				ExFreePool(parameter);
				return;
			}
			else
			{
				sendLogs(currentProcessId,L"LOAD_DRIVER", L"1,0,s,DriverName->undefined");
				cleanMonitoredProcessList();
				if(parameter)
					ExFreePool(parameter);
				return;
			}
		}
	}
}

