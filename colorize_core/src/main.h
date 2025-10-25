#pragma once

void Init();

void Color(sol::this_state ts, uintptr_t pPed, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void Uncolor(sol::this_state ts, uintptr_t pPed);
void Unload(sol::this_state ts);

void __fastcall Hooked_CEntity_Render(void* _this);