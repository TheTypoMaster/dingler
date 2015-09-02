@echo off
tools\gyp\gyp.bat --depth=. -Goutput_dir=C:\Project\dingler\out -f cmake -DMSVS_VERSION=2013 -DMSVS_OS_BITS=64 -Ibuild\common.gypi v8\tools\gyp\v8.gyp
