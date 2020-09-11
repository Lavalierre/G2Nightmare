// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	
	xGameController xGameController::oInstance;

	void xGameController::Init()
	{

		// Buffs
		AddBuffArch("BURNING", "Горение", "VOB_BURN", "VOB_BURN");
		AddBuffArch("WARM", "Теплота", "NULL");
		AddBuffArch("BLEEDING", "Кровотечение", "NULL");
		AddBuffArch("FREEZE", "Обморожение", "NULL");
		AddBuffArch("STRETCH", "Травма", "NULL");
		AddBuffArch("TOXIC", "Интоксикация", "NULL");
		AddBuffArch("WET", "Влага", "NULL");
		AddBuffArch("WEAK", "Слабость", "NULL");
		AddBuffArch("FIREDRAGONBUFF", "Противник огня", "SPELLFX_INCOVATION_RED");
		AddBuffArch("ICEDRAGONBUFF", "Противник холода", "SPELLFX_INCOVATION_BLUE");
		AddBuffArch("ROCKDRAGONBUFF", "Противник камня", "SPELLFX_INCOVATION_WHITE");
		AddBuffArch("SWAMPDRAGONBUFF", "Противник земли", "SPELLFX_INCOVATION_GREEN");

		AddBuffArch("DESEASE", "Болезнь", "NULL");

		AddBuffArch("INVISIBILITY", "Невидимость", "SPELLFX_LIGHTSTAR_WHITE", "NULL", "NULL");
		AddBuffArch("FIRERESIST", "Огнеупорность", "SPELLFX_LIGHTSTAR_RED", "NULL", "NULL");
		AddBuffArch("ENRAGE", "Ярость", "SPELLFX_LIGHTSTAR_VIOLET", "VOB_BURN_CHILD5", "NULL");
		AddBuffArch("STRENGTH", "Сила", "SPELLFX_LIGHTSTAR_YELLOW", "NULL", "NULL");

		// Heavy armor
		AddHeavyArmor("ITAR_DJG_CRAWLER");
		AddHeavyArmor("ITAR_MIL_M");
		AddHeavyArmor("ITAR_PAL_M");
		AddHeavyArmor("ITAR_PAL_H");
		AddHeavyArmor("ITAR_SLD_M");
		AddHeavyArmor("ITAR_SLD_H");
		AddHeavyArmor("ITAR_DJG_L");
		AddHeavyArmor("ITAR_DJG_M");
		AddHeavyArmor("ITAR_DJG_H");
		AddHeavyArmor("ITAR_KDF_H");
		AddHeavyArmor("ITAR_KDW_H");
		AddHeavyArmor("ITAR_PIR_H_ADDON");
		AddHeavyArmor("ITAR_THORUS_ADDON");
		AddHeavyArmor("ITAR_LESTER");
		AddHeavyArmor("ITAR_GOVERNOR");
		AddHeavyArmor("ITAR_MAYAZOMBIE_ADDON");
		AddHeavyArmor("ITAR_BLOODWYN_ADDON");
		AddHeavyArmor("ITAR_OREBARON_ADDON");
		AddHeavyArmor("ITAR_CORANGAR");
		AddHeavyArmor("ITAR_PAL_SKEL");
		AddHeavyArmor("ITAR_XARDAS");
		AddHeavyArmor("ITAR_RAVEN_ADDON");
		AddHeavyArmor("ITAR_DEMENTOR");


		// Inv weight bar
		invBar = new oCViewStatusBar();
		screen->InsertItem(invBar);
		invBar->Init(100, 7500, 1.0F);
		invBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_misc.tga", "");
		invBar->RemoveItem(invBar);
		// Toxic bar
		toxicBar = new oCViewStatusBar();
		screen->InsertItem(toxicBar);
		toxicBar->Init(100, 7500, 1.0F);
		toxicBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_Toxic.tag", "");
		toxicBar->RemoveItem(toxicBar);
	}

	void xGameController::Process()
	{
		ProcessBuffsUI();

		// InGame Timer

		if (zCMenu::inGameMenu && !ogame->singleStep)
		{
			if (!player->IsDead())
				timerSecs = gameMan->GetPlaytimeSeconds();

			int secs = timerSecs;
			int mins = secs / 60;
			secs = secs % 60;
			int hours = mins / 60;
			mins = mins % 60;

			char buffer[64];
			sprintf(buffer, "Время в игре: %02d:%02d:%02d", hours, mins, secs);
			screen->Print(screen->anx(10), screen->any(10), buffer);
		}
	}

	void xGameController::ProcessBuffsUI()
	{
		xNpc* xplayer = dynamic_cast<xNpc*>(player);
		if (xplayer)
		{
			std::vector<PlayerBuff*> buffs = xplayer->GetBuffList();
			if (buffs.size() != 0)
			{
				int bottomtop = 8192 - screen->any(90);
				int i = 0;
				for (PlayerBuff* buff : buffs)
				{
					char buffer[64];
					if (!buff->infinite)
					{
						sprintf(buffer, "%s (%d сек.)", buff->archType->name.ToChar(), buff->duration / 1000);
					}
					else
					{
						if (buff->type == "DESEASE")
							sprintf(buffer, "%s (x%d)", buff->archType->name.ToChar(), xplayer->GetDeseaseLevel());
						else
							sprintf(buffer, "%s", buff->archType->name.ToChar());
					}

					screen->Print(screen->anx(10), bottomtop - (200 * i), buffer);
					i++;
				}
			}
		}
	}

	void xGameController::DefineExternals()
	{
		parser->DefineExternal("Mod_AddBuff_Invisibility", Mod_AddBuff_Invisibility, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_AddBuff_FireResistance", Mod_AddBuff_FireResistance, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_AddBuff_Enrage", Mod_AddBuff_Enrage, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_AddBuff_Strength", Mod_AddBuff_Strength, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_AddBuff_Burn", Mod_AddBuff_Burn, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_AddToxic", Mod_AddToxic, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_ClearDesease", Mod_ClearDesease, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
		parser->DefineExternal("Mod_TryingToTeleport", Mod_TryingToTeleport, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
	}

	void xGameController::AddBuffArch(string type, string name, string startFX, string tickFX, string endFX)
	{
		auto it = vBuffTypes.find(type);
		if (it == vBuffTypes.end())
		{
			BuffArch* newBuff = new BuffArch;
			newBuff->name = name;
			newBuff->startFX = startFX;
			newBuff->tickFX = tickFX;
			newBuff->endFX = endFX;
			vBuffTypes.insert(std::pair<string, BuffArch*>(type, newBuff));
		}
	}

	BuffArch* xGameController::GetBuffArch(string type)
	{
		auto it = vBuffTypes.find(type);
		if (it != vBuffTypes.end())
		{
			return it->second;
		}

		return nullptr;
	}

	void xGameController::AddHeavyArmor(string instance)
	{
		vHeavyArmor.push_back(instance);
	}

	bool xGameController::IsArmorHeavy(string instance)
	{
		for (string str : vHeavyArmor)
		{
			if (str == instance)
				return true;
		}

		return false;
	}
}