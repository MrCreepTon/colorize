#include "pch.h"
#include <mutex>
#include <unordered_map>
#include "MinHook.h"
#include "lua_module.h"
#include "main.h"

#define CEntity_Render_Address 0x534310
#define RpClumpForAllAtomics_Address 0x749B70
#define RpGeometryForAllMaterials_Address 0x74C790

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} sColor;

std::mutex lua_mutex;
std::unordered_map<uintptr_t, sColor> peds;

typedef void(__thiscall* tCEntityRender)(void*);
tCEntityRender origCEntityRender = nullptr;

typedef void(__cdecl* tRpClumpForAllAtomics)(void*, void*(__cdecl*)(void*, void*), void*);
typedef void(__cdecl* tRpGeometryForAllMaterials)(void*, void* (__cdecl*)(void*, void*), void*);

tRpClumpForAllAtomics RpClumpForAllAtomics = reinterpret_cast<tRpClumpForAllAtomics>(RpClumpForAllAtomics_Address);
tRpGeometryForAllMaterials RpGeometryForAllMaterials = reinterpret_cast<tRpGeometryForAllMaterials>(RpGeometryForAllMaterials_Address);

sol::table open(sol::this_state ts)
{
	sol::state_view lua(ts);
	sol::table module = lua.create_table();
	
	module.set_function("color", &Color);
	module.set_function("uncolor", &Uncolor);
	module.set_function("unload", &Unload);
	
	Init();

	return module;
}

void Init() {
	MH_Initialize();
	MH_CreateHook((void*)CEntity_Render_Address, &Hooked_CEntity_Render, (void**)&origCEntityRender);
	MH_EnableHook((void*)CEntity_Render_Address);
}

void Color(sol::this_state ts, uintptr_t pPed, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	std::lock_guard<std::mutex> lock(lua_mutex);
	peds[pPed] = { r, g, b, a };
}

void Uncolor(sol::this_state ts, uintptr_t pPed) {
	std::lock_guard<std::mutex> lock(lua_mutex);
	peds.erase(pPed);
}

void Unload(sol::this_state ts) {
	MH_DisableHook((void*)CEntity_Render_Address);
}

void* __cdecl MaterialTextureCallback(void* pMaterial, void* pData) {
	*reinterpret_cast<sColor*>(reinterpret_cast<uintptr_t>(pMaterial) + 0x04) = *reinterpret_cast<sColor*>(pData);
	return pMaterial;
}

void* __cdecl AtomicTextureCallback(void* pAtomic, void* pData) {
	uintptr_t pGeometry = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(pAtomic) + 0x18);
	*reinterpret_cast<int*>(pGeometry + 0x8) |= 0x40;
	RpGeometryForAllMaterials(
		reinterpret_cast<void*>(pGeometry),
		MaterialTextureCallback,
		pData
	);
	return pAtomic;
}

void SetEntityModelColor(uintptr_t pEntity, sColor color) {
	uintptr_t pRwObject = *reinterpret_cast<uintptr_t*>(pEntity + 0x18);
	RpClumpForAllAtomics(
		reinterpret_cast<void*>(pRwObject),
		AtomicTextureCallback,
		&color
	);
}

void __fastcall Hooked_CEntity_Render(void* _this) {
	std::lock_guard<std::mutex> lock(lua_mutex);
	
	uintptr_t pPed = reinterpret_cast<uintptr_t>(_this);

	bool pedExists = peds.find(pPed) != peds.end();

	if (pedExists) {
		sColor color = peds[pPed];
		SetEntityModelColor(pPed, color);
	}

	origCEntityRender(_this);

	if (pedExists) {
		SetEntityModelColor(pPed, { 255, 255, 255, 255 });
	}
}

SOL_MODULE_ENTRYPOINT(open);
