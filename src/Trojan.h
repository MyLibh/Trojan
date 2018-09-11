#pragma once

#ifndef __TROJAN_H_INCLUDED__
#define __TROJAN_H_INCLUDED__

#include <Windows.h>

#define LARGE_BUFFER_LENGTH 512

PTCHAR GetFilename(const PTCHAR filepath, size_t length);

BOOL InitTrojan();
VOID StartTrojan();

#endif /* __TROJAN_H_INCLUDED__ */