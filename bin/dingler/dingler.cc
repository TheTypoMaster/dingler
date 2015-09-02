// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "build/build_config.h"
#include "bin/dingler/dingler_main.h"

#if defined(OS_WIN)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <tchar.h>
int main(int argc, const char* argv[]) {
//int APIENTRY WinMain(_In_ HINSTANCE hInstance,
// _In_opt_ HINSTANCE hPrevInstance,
// _In_ LPSTR    lpCmdLine,
// _In_ int       nCmdShow) {
#else
int main(int argc, const char** argv) {
#endif
 dingler::MainParams params;
//#if defined(OS_WIN)
 //params.instance = hPrevInstance;
//#else
 //params.argc = argc;
 //params.argv = argv;
//#endif
 params.argc = argc;
 params.argv = argv;
 return dingler::Main(params);
}