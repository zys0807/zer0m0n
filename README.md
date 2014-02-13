zer0m0n v0.4 (DEVELOPMENT BRANCH)
=================================

To-do :
+ Eliminate bugs :]
+ Cr0 reg trick => multiprocessor issues.
+ Use inverted IRP calls with kernel buffer instead of filter comm. ports :]
+ Add anti-detection features (cuckoo/VM files/process/reg/connections)
+ Handle machine poweroff
+ Add monitored functions/events
+ Handle file deletion
+ win7 x86 support
+ x64 support (get rid of SSDT hooks)
+ Handle SSDT hooks race conditions (perform legitimate calls with copied parameters)
+ fix random socket desynch
+ etc.

v0.4 changes :
+ more anti VM detection features
+ log new loaded modules through ZwCreateSection hook 

v0.3 changes :
+ fix minor bugs
+ fix ZwTerminateProcess race condition (notify analyzer.py of process termination)
+ fix hook ZwDelayExecution => log the call before executing it
+ Signatures :]
+ some anti VM (virtualbox) detection features (based on pafish PoC)
+ ZwReadVirtualMemory hook
+ ZwResumeThread hook
+ handle driver execution (abort analysis)

v0.2 changes :
+ ZwDeviceIoControlFile hook
+ ZwCreateMutant hook
+ ZwDelayExecution hook
+ ZwTerminateProcess hook
+ Fixed deadlock issue (FltSendMessage infinite wait switched to 100ms timeout)
+ Fixed performance issues (drop) using userland app multithreading
