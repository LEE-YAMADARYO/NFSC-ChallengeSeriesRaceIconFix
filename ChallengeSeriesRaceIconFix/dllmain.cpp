// Copyright(C) 2025 YAMADA RYO
// 此 ASI 插件用于修复 Need for Speed Carbon 自定挑战赛图标显示问题
// 该代码根据 MIT 许可证发布
// 著作权所有

// 警告：游戏将挑战赛按索引分组，每组有3个挑战赛，同一个事件组中的所有挑战赛应用相同的图标
// 这意味着您在改变其中一场挑战赛图标时，同一行中所有的图标都将会同时更变
// 这可能会在未来修复或解决
#include "pch.h"
#include <windows.h>
#include "MinHook\include\MinHook.h" // 请自行获取 MinHook
#include <cstdio>

// 定义原始函数的类型
// 函数地址: 0x004AA3F0
// 函数签名: char __stdcall DALChallenge::GetChallengeEventIcon(_DWORD *EventIconHash, unsigned int ChallengeHash)
typedef char(__stdcall* GetChallengeEventIcon_t)(unsigned int* EventIconHash, unsigned int ChallengeHash);

// 保存原始函数地址的指针
GetChallengeEventIcon_t fpOriginalGetChallengeEventIcon = NULL;

// 定义需要修改的挑战赛哈希值
// 您可以根据自身需求增加或移除常量定义
const unsigned int CUSTOM_CHALLENGE_HASH_1 = 0x00000000;
const unsigned int CUSTOM_CHALLENGE_HASH_2 = 0x00000000;
const unsigned int CUSTOM_CHALLENGE_HASH_3 = 0x00000000;

// 图标哈希值
// 您可以根据自身需求增加或移除常量定义
const unsigned int CHALLENGERACE_ICON_HASH_1 = 0x00000000;
const unsigned int CHALLENGERACE_ICON_HASH_2 = 0x00000000;
const unsigned int CHALLENGERACE_ICON_HASH_3 = 0x00000000;
// 您可以在 Binary 中查看图标的哈希值，其中 BinKey 即为它们的哈希值
// 对于追击挑战赛，游戏默认调用 FRONTEND\FrontB1.lzc 文件中的 TPKBlocks\FRONTENDTEXTURES 纹理集合的图标

char __stdcall DetourGetChallengeEventIcon(unsigned int* EventIconHash, unsigned int ChallengeHash) {

    // 检查当前的哈希值是否为上文所定义的挑战赛 1
    if (ChallengeHash == CUSTOM_CHALLENGE_HASH_1) {
        *EventIconHash = CHALLENGERACE_ICON_HASH_1; // 使用 CHALLENGERACE_ICON_HASH_1 图标
        return 1;
    }
    // 检查当前的哈希值是否为上文所定义的挑战赛 2
    else if (ChallengeHash == CUSTOM_CHALLENGE_HASH_2) {
        *EventIconHash = CHALLENGERACE_ICON_HASH_2; // 使用 CHALLENGERACE_ICON_HASH_2 图标
        return 1;
    }
    // 检查当前的哈希值是否为上文所定义的挑战赛 3
    else if (ChallengeHash == CUSTOM_CHALLENGE_HASH_3) {
        *EventIconHash = CHALLENGERACE_ICON_HASH_3; // 使用 CHALLENGERACE_ICON_HASH_3 图标
        return 1;
    }
    // 若不是上文所定义的挑战赛，则调用原始函数
    else {
        return fpOriginalGetChallengeEventIcon(EventIconHash, ChallengeHash);
    }
}

// 初始化 Hook
void InitializeHook() {
    if (MH_Initialize() != MH_OK) {
        return;
    }
    LPVOID pTarget = (LPVOID)0x004AA3F0;
    if (MH_CreateHook(pTarget, DetourGetChallengeEventIcon, (LPVOID*)&fpOriginalGetChallengeEventIcon) != MH_OK) {
        return;
    }
    if (MH_EnableHook(pTarget) != MH_OK) {
        return;
    }
}

// DLL 入口点
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        InitializeHook();
        break;
    case DLL_PROCESS_DETACH:
        MH_Uninitialize();
        break;
    }
    return TRUE;
}
