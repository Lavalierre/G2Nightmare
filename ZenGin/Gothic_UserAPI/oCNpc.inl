// Supported with union (c) 2020 Union team

// User API for oCNpc
// Add your methods here

void Equip_Mod(Gothic_II_Addon::oCItem* item);
int CanSense_Mod(Gothic_II_Addon::zCVob* vob);

int EV_DrawWeapon_Mod(Gothic_II_Addon::oCMsgWeapon* csg);
int EV_DrawWeapon1_Mod(Gothic_II_Addon::oCMsgWeapon* csg);
int EV_DrawWeapon2_Mod(Gothic_II_Addon::oCMsgWeapon* csg);

void OnDamage_Mod(Gothic_II_Addon::oCNpc::oSDamageDescriptor&);