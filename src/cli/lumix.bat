@echo off
set "batchScriptPath=%~dp0"
set "slicedPath=%batchScriptPath:~0,-4%"
%slicedPath%compiler\build\run.exe %1