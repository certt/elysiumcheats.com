#pragma once

#include "SDK.h"

#include "VMTHook.h"

#include "Hooks.h"
#include "Triggerbot.h"
#include "Aimbot.h"
#include "Visuals.h"
#include "CMenu.h"
#include "Changers.h"

#define TEXT_KEY /*PtPg8c1Ge5KYiaDy3Qg73NBgLvLWxAWb*/Xor<0x62,33,0x41101FAD>("\x32\x17\x34\x02\x5E\x04\x59\x2E\x0F\x5E\x27\x34\x07\x0E\x34\x08\x41\x22\x13\x42\x45\x39\x3A\x1E\x36\x0D\x30\x2A\x06\x3E\xD7\xE3"+0x41101FAD).s
#define TEXT_IV /*RNuOq6zGR0FTLJ35*/Xor<0x7E,17,0x640474C2>("\x2C\x31\xF5\xCE\xF3\xB5\xFE\xC2\xD4\xB7\xCE\xDD\xC6\xC1\xBF\xB8"+0x640474C2).s
#define BAN_KEY /*3ir5QTKi0R2E4BBoId7EdFRXjZZZCx2w*/Xor<0x2A,33,0x283FDEA1>("\x19\x42\x5E\x18\x7F\x7B\x7B\x58\x02\x61\x06\x70\x02\x75\x7A\x56\x73\x5F\x0B\x78\x5A\x79\x12\x19\x28\x19\x1E\x1F\x05\x3F\x7A\x3E"+0x283FDEA1).s
#define BAN_IV /*S0IBFMKCg1LTqJ8W*/Xor<0x52,17,0xAF361FA7>("\x01\x63\x1D\x17\x10\x1A\x13\x1A\x3D\x6A\x10\x09\x2F\x15\x58\x36"+0xAF361FA7).s

#ifdef _DEBUG
#else
#include "ClientDefence.h"
#include "Initialize.h"
#endif