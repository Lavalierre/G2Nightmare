// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {

	HOOK Ivk_oCNpc_Equip					AS(&oCNpc::Equip, &oCNpc::Equip_Mod);
	HOOK Ivk_oCNpc_Sense					AS(&oCNpc::CanSense, &oCNpc::CanSense_Mod);
	HOOK Ivk_oCNpc_Draw						AS(&oCNpc::EV_DrawWeapon, &oCNpc::EV_DrawWeapon_Mod);
	HOOK Ivk_oCNpc_Draw1					AS(&oCNpc::EV_DrawWeapon1, &oCNpc::EV_DrawWeapon1_Mod);
	HOOK Ivk_oCNpc_Draw2					AS(&oCNpc::EV_DrawWeapon2, &oCNpc::EV_DrawWeapon2_Mod);
	HOOK Ivk_oCNpc_OnDamage					AS(&oCNpc::OnDamage, &oCNpc::OnDamage_Mod);

	HOOK Ivk_oCGame_UpdatePlayerStatus		AS(&oCGame::UpdatePlayerStatus, &oCGame::UpdatePlayerStatus_Mod);
	HOOK Ivk_oCGame_UpdateScreenResolution	AS(&oCGame::UpdateScreenResolution, &oCGame::UpdateScreenResolution_Mod);
	HOOK Ivk_oCGame_ShowStatus				AS(&oCGame::SetShowPlayerStatus, &oCGame::SetShowPlayerStatus_Mod);

	HOOK Ivk_oCAIHuman_SlowMove				AS(&oCAIHuman::PC_SlowMove, &oCAIHuman::PC_SlowMove_Mod);
	HOOK Ivk_oCAIHuman_Sneak				AS(&oCAIHuman::PC_Sneak, &oCAIHuman::PC_Sneak_Mod);
	HOOK Ivk_oCAIHuman_Strafe				AS(&oCAIHuman::PC_Strafe, &oCAIHuman::PC_Strafe_Mod);
	HOOK Ivk_oCAIHuman_SpecialMove			AS(&oCAIHuman::PC_SpecialMove, &oCAIHuman::PC_SpecialMove_Mod);

	HOOK Ivk_oCZoneMusic_ProcessZoneList	AS(&oCZoneMusic::ProcessZoneList, &oCZoneMusic::ProcessZoneList_Mod);

	void oCNpc::OnDamage_Mod(Gothic_II_Addon::oCNpc::oSDamageDescriptor& descDamage)
	{

		zCPar_Symbol* pSymbol = parser->GetSymbol("NPC_BURN_DAMAGE_POINTS_PER_INTERVALL");
		if (pSymbol)
		{
			int intervalDamage = 0;
			pSymbol->SetValue(intervalDamage, 0);
		}

		if (this == player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				// Applying buffs

				switch (descDamage.nSpellID)
				{
				case SPL_CHARGEFIREBALL:
				case SPL_FIREBOLT:
				case SPL_INSTANTFIREBALL:
				case SPL_PYROKINESIS:
				case SPL_FIRESTORM:
				case SPL_DEATHBALL:
				case SPL_DEATHBOLT:
				case SPL_FIRERAIN:
					xplayer->AddBuff("BURNING", 5000, 0, 5 * descDamage.nSpellLevel, oEDamageType_Fire);
					xplayer->AddBuff("WARM", 5000);
					break;
				case SPL_ZAP:
				case SPL_LIGHTNINGFLASH:
				case SPL_THUNDERBALL:
				case SPL_BELIARSRAGE:
					if (xplayer->HasBuff("WET") != nullptr || xplayer->HasLongBuff("WET") != nullptr)
					{
						descDamage.fDamageTotal *= 2;
						descDamage.aryDamage[oEDamageType_Magic] *= 2;
					}
					break;
				case SPL_ICEBOLT:
				case SPL_ICECUBE:
				case SPL_ICEWAVE:
				case SPL_CONCUSSIONBOLT:
				case SPL_ICELANCE:
					xplayer->AddBuff("FREEZE", 8000, 0, 0, oEDamageType_Magic);
					break;
				case SPL_GEYSER:
				case SPL_WATERFIST:
					xplayer->AddBuff("WET", 10000, 0, 5, oEDamageType_Magic);
					break;
				case SPL_THUNDERSTORM:
					xplayer->AddBuff("WET", 10000, 0, 5, oEDamageType_Magic);
					xplayer->AddBuff("FREEZE", 8000, 0, 0, oEDamageType_Magic);
					if (xplayer->HasBuff("WET") != nullptr || xplayer->HasLongBuff("WET") != nullptr)
					{
						descDamage.fDamageTotal *= 2;
						descDamage.aryDamage[oEDamageType_Magic] *= 2;
					}
					break;
				}

				if (descDamage.pNpcAttacker)
				{
					zSTRING instance = descDamage.pNpcAttacker->GetInstanceName().Upper();
					
					if (instance == "DRAGON_FIRE" ||
						instance == "DRAGON_FIRE_ISLAND" ||
						instance == "DRAGON_ICE" ||
						instance == "DRAGON_ROCK" ||
						instance == "DRAGON_SWAMP" ||
						instance == "DRAGON_UNDEAD" ||
						instance == "DEMON" ||
						instance == "SUMMONED_DEMON" ||
						instance == "XARDAS_DT_DEMON1" ||
						instance == "XARDAS_DT_DEMON2" ||
						instance == "XARDAS_DT_DEMON3" ||
						instance == "XARDAS_DT_DEMON4" ||
						instance == "XARDAS_DT_DEMON5" ||
						instance == "XARDAS_DT_DEMONLORD" ||
						instance == "DEMONLORD")
					{
						xplayer->AddBuff("BURNING", 5000, 0, 10, oEDamageType_Fire);
						xplayer->AddBuff("WARM", 5000);
					}
					else if (instance == "SWAMPRAT" ||
						instance == "GIANT_RAT" ||
						instance == "YGIANT_RAT" ||
						instance == "MOLERAT" ||
						instance == "SCAVENGER" ||
						instance == "SCAVENGER_DEMON" ||
						instance == "SWAMPSHARK" ||
						instance == "GIANT_DESERTRAT" ||
						instance == "BLATTCRAWLER" ||
						instance == "SWAMPRAT" ||
						instance == "GIANT_BUG" ||
						instance == "ZOMBIE01" ||
						instance == "ZOMBIE02" ||
						instance == "ZOMBIE03" ||
						instance == "ZOMBIE04" ||
						instance == "ZOMBIE_ADDON_KNECHT" ||
						instance == "ZOMBIE_ADDON_BLOODWYN" ||
						instance == "PAL_ZOMBIE01" ||
						instance == "PAL_ZOMBIE02" ||
						instance == "PAL_ZOMBIE03" ||
						instance == "PAL_ZOMBIE04" ||
						instance == "MAYAZOMBIE01" ||
						instance == "MAYAZOMBIE02" ||
						instance == "MAYAZOMBIE03" ||
						instance == "MAYAZOMBIE04" ||
						instance == "MAYAZOMBIE04_TOTENW" ||
						instance == "SUMMONED_ZOMBIE")
					{
						int nPercentage = rand() % 100;
						if (nPercentage < 5)
						{
							xplayer->AddDesease();
						}
					}
					else if (instance == "BLOODFLY" ||
						instance == "YBLOODFLY" ||
						instance == "SLEEPFLY" ||
						instance == "BLATTCRAWLER" ||
						instance == "LURKER" ||
						instance == "KERVO_LURKER1" ||
						instance == "KERVO_LURKER2" ||
						instance == "KERVO_LURKER3" ||
						instance == "KERVO_LURKER4" ||
						instance == "KERVO_LURKER5" ||
						instance == "KERVO_LURKER6" ||
						instance == "BEACHLURKER1" ||
						instance == "BEACHLURKER2" ||
						instance == "BEACHLURKER3")
					{
						xplayer->AddToxic(100);
					}
					else if (instance == "BLOODHOUND" ||
						instance == "ORCBITER" ||
						instance == "RAZOR" ||
						instance == "CANYONRAZOR01" ||
						instance == "CANYONRAZOR02" ||
						instance == "CANYONRAZOR03" ||
						instance == "CANYONRAZOR04" ||
						instance == "CANYONRAZOR05" ||
						instance == "CANYONRAZOR06" ||
						instance == "CANYONRAZOR07" ||
						instance == "CANYONRAZOR08" ||
						instance == "CANYONRAZOR09" ||
						instance == "CANYONRAZOR10" ||
						instance == "DRAGONSNAPPER" ||
						instance == "GAANS_SNAPPER" ||
						instance == "MINECRAWLERWARRIOR" ||
						instance == "SHADOWBEAST" ||
						instance == "BEACHSHADOWBEAST1")
					{
						xplayer->AddBuff("BLEEDING", 5000, 0, 5, oEDamageType_Edge);
					}
				}

				// NIGHT TIME BUFF

				zCSkyControler_Outdoor* skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(GetHomeWorld()->GetActiveSkyControler());
				if (skyCtrl->masterTime >= 0.3F && skyCtrl->masterTime <= 0.75F)
				{
					descDamage.aryDamage[oEDamageType_Blunt] *= 2;
					descDamage.aryDamage[oEDamageType_Edge] *= 2;
					descDamage.fDamageTotal *= 2;
				}

				// ROCK DRAGON DEBUFF

				if (xplayer->HasBuff("ROCKDRAGONDEBUFF"))
				{
					descDamage.aryDamage[oEDamageType_Blunt] *= 2;
					descDamage.aryDamage[oEDamageType_Edge] *= 2;
					descDamage.fDamageTotal *= 2;
				}


				// FIRE RESISTANCE POTION

				if (this->HasFlag(descDamage.enuModeDamage, oEDamageType_Fire));
				{
					if (xplayer->HasBuff("FIRERESIST") != nullptr)
						return;
				}

				// BLEEDING DEBUFF

				if (this->HasFlag(descDamage.enuModeDamage, oEDamageType_Point))
				{
					xplayer->AddBuff("BLEEDING", 8 * 1000, 10, 5, oEDamageType_Edge);
				}
				else if (this->HasFlag(descDamage.enuModeDamage, oEDamageType_Edge) && descDamage.pItemWeapon != NULL)
				{
					int nPercentage = rand() % 100;
					if (nPercentage < 10)
					{
						xplayer->AddBuff("BLEEDING", 8 * 1000, 10, 5, oEDamageType_Edge);
					}
				}

			}
		}

		xNpc* xattacker = dynamic_cast<xNpc*>(descDamage.pVobAttacker);
		if (xattacker)
		{

			// ENRAGE POTION

			if (xattacker->HasBuff("ENRAGE") != nullptr)
			{
				// Separated damag

				for (int i = 0; i < oEDamageIndex_MAX; i++)
				{
					descDamage.aryDamage[i] = descDamage.aryDamage[i] * 2;
				}

				// Total damage

				descDamage.fDamageTotal *= 2;
			}
		}

		THISCALL(Ivk_oCNpc_OnDamage)(descDamage);

		// Permanent buffs
		if (descDamage.bIsDead)
		{
			zSTRING instance = this->GetInstanceName().Upper();
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				if (instance == "DRAGON_FIRE")
				{
					xplayer->ClearPermanentBuffs();
					xplayer->AddLongBuff("FIREDRAGONBUFF", 0, 0, 32, true);
				}

				if (instance == "DRAGON_ICE")
				{
					xplayer->ClearPermanentBuffs();
					xplayer->AddLongBuff("ICEDRAGONBUFF", 0, 0, 32, true);
				}

				if (instance == "DRAGON_ROCK")
				{
					xplayer->ClearPermanentBuffs();
					xplayer->AddLongBuff("ROCKDRAGONBUFF", 0, 0, 32, true);
				}

				if (instance == "DRAGON_SWAMP")
				{
					xplayer->ClearPermanentBuffs();
					xplayer->AddLongBuff("SWAMPDRAGONBUFF", 0, 0, 32, true);
				}
			}
		}
	}

	zBOOL oCNpc::CanSense_Mod(zCVob* vob)
	{
		xNpc* xvob = dynamic_cast<xNpc*>(vob);
		xNpc* xplayer = dynamic_cast<xNpc*>(player);
		if (xvob && xplayer && xvob == xplayer)
		{
			if (xplayer->HasBuff("INVISIBILITY") != nullptr)
				return FALSE;
		}

		return THISCALL(Ivk_oCNpc_Sense)(vob);
	}

	zBOOL oCNpc::EV_DrawWeapon_Mod(oCMsgWeapon* csg)
	{
		if (this == player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer->HasBuff("INVISIBILITY") != nullptr)
				xplayer->DeleteBuff("INVISIBILITY");
		}

		return THISCALL(Ivk_oCNpc_Draw)(csg);
	}

	zBOOL oCNpc::EV_DrawWeapon1_Mod(oCMsgWeapon* csg)
	{
		if (this == player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer->HasBuff("INVISIBILITY") != nullptr)
				xplayer->DeleteBuff("INVISIBILITY");
		}

		return THISCALL(Ivk_oCNpc_Draw1)(csg);
	}

	zBOOL oCNpc::EV_DrawWeapon2_Mod(oCMsgWeapon* csg)
	{
		if (this == player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer->HasBuff("INVISIBILITY") != nullptr)
				xplayer->DeleteBuff("INVISIBILITY");
		}

		return THISCALL(Ivk_oCNpc_Draw2)(csg);
	}

	void oCNpc::Equip_Mod(oCItem* item)
	{
		if (item)
		{
			int cat = inventory2.GetCategory(item);

			if (cat == INV_MAGIC && item->HasFlag(ITM_FLAG_RING))
			{
				if (item->HasFlag(ITM_FLAG_ACTIVE))
				{
					RemoveItemEffects(item);
					item->ClearFlag(ITM_FLAG_ACTIVE);
				}
				else
				{
					oCItem* ring = NULL;
					inventory2.UnpackCategory();
					int numItems = inventory2.GetNumItemsInCategory();
					int usedRings = 0;
					for (int i = 0; i < numItems; i++)
					{
						ring = inventory2.GetItem(i);
						if (ring && ring->HasFlag(ITM_FLAG_RING) && ring->HasFlag(ITM_FLAG_ACTIVE))
						{
							usedRings++;
							if (usedRings >= 4)
								return;
						}
					}

					AddItemEffects(item);
					item->SetFlag(ITM_FLAG_ACTIVE);
				}
			}
			else
			{
				THISCALL(Ivk_oCNpc_Equip)(item);
			}
		}
	}

	void oCGame::SetShowPlayerStatus_Mod(zBOOL show)
	{
		if (!show)
		{
			screen->RemoveItem(xGameController::GetInstance().invBar);
			screen->RemoveItem(xGameController::GetInstance().toxicBar);
		}

		THISCALL(Ivk_oCGame_ShowStatus)(show);
	}

	void oCGame::UpdatePlayerStatus_Mod()
	{
		THISCALL(Ivk_oCGame_UpdatePlayerStatus)();

		oCViewStatusBar* invBar = xGameController::GetInstance().invBar;
		oCViewStatusBar* toxicBar = xGameController::GetInstance().toxicBar;

		if (!player)				return;
		if (!GetShowPlayerStatus())	return;
		if (invBar == nullptr)		return;

		xNpc* xplayer = dynamic_cast<xNpc*>(player);

		screen->RemoveItem(invBar);
		screen->RemoveItem(toxicBar);

		if (player->inventory2.IsOpen())
		{
			if (xplayer)
			{
				int nMaxInvWeight = xplayer->GetMaxInvWeight();
				if (nMaxInvWeight > 0)
				{
					screen->InsertItem(invBar);
					invBar	->	SetMaxRange	(0, nMaxInvWeight);
					invBar	->	SetRange	(0, nMaxInvWeight);
					invBar	->	SetValue	(xplayer->inventory2.GetNumItemsInCategory());
				}
			}
		}

		if (xplayer && xplayer->GetToxic() > 0)
		{
			screen->InsertItem(toxicBar);
			toxicBar	->	SetMaxRange(0, xplayer->GetMaxToxic());
			toxicBar	->	SetRange(0, xplayer->GetMaxToxic());
			toxicBar	->	SetValue(xplayer->GetToxic());
		}
	}

	void oCGame::UpdateScreenResolution_Mod()
	{
		THISCALL(Ivk_oCGame_UpdateScreenResolution)();

		oCViewStatusBar* invBar = xGameController::GetInstance().invBar;
		oCViewStatusBar* toxicBar = xGameController::GetInstance().toxicBar;

		const int barSizeX = 180;
		const int barSizeY = 20;

		int bottomTop = 8192 - screen->any(10 + barSizeY * 2);
		int xs, ys;

		screen->InsertItem(invBar);
		screen->InsertItem(toxicBar);

		// Max Load bar
		invBar->Init(screen->anx(10), bottomTop, 1.0F);
		// Toxic bar
		toxicBar->Init(0, 0, 1.0F);
		toxicBar->GetSize(xs, ys);
		toxicBar->SetPos((8192 - xs) / 2.0f, bottomTop);


		screen->RemoveItem(invBar);
		screen->RemoveItem(toxicBar);
	}

	zBOOL oCAIHuman::PC_SlowMove_Mod(zBOOL pressed)
	{
		xNpc* xplayer = dynamic_cast<xNpc*>(player);
		if (xplayer)
		{
			if (xplayer->inventory2.GetNumItemsInCategory() <= xplayer->GetMaxInvWeight() &&
				xplayer->HasBuff("INVISIBILITY") == nullptr &&
				xplayer->HasBuff("STRETCH") == nullptr &&
				xplayer->HasBuff("FREEZE") == nullptr &&
				xplayer->HasLongBuff("FREEZE") == nullptr)
				return THISCALL(Ivk_oCAIHuman_SlowMove)(pressed);
		}

		return FALSE;
	}

	zBOOL oCAIHuman::PC_Sneak_Mod(zBOOL pressed)
	{
		xNpc* xplayer = dynamic_cast<xNpc*>(player);
		if (xplayer)
		{
			if (xplayer->inventory2.GetNumItemsInCategory() <= xplayer->GetMaxInvWeight() &&
				xplayer->HasBuff("INVISIBILITY") == nullptr &&
				xplayer->HasBuff("STRETCH") == nullptr &&
				xplayer->HasBuff("FREEZE") == nullptr &&
				xplayer->HasLongBuff("FREEZE") == nullptr)
				return THISCALL(Ivk_oCAIHuman_Sneak)(pressed);
		}

		return FALSE;
	}

	zBOOL oCAIHuman::PC_Strafe_Mod(zBOOL pressed)
	{
		xNpc* xplayer = dynamic_cast<xNpc*>(player);
		if (xplayer)
		{
			if (xplayer->inventory2.GetNumItemsInCategory() <= xplayer->GetMaxInvWeight() &&
				xplayer->HasBuff("INVISIBILITY") == nullptr &&
				xplayer->HasBuff("STRETCH") == nullptr &&
				xplayer->HasBuff("FREEZE") == nullptr &&
				xplayer->HasLongBuff("FREEZE") == nullptr)
				return THISCALL(Ivk_oCAIHuman_Strafe)(pressed);
		}

		return FALSE;
	}

	zBOOL oCAIHuman::PC_SpecialMove_Mod(zBOOL pressed)
	{
		xNpc* xplayer = dynamic_cast<xNpc*>(player);
		if (xplayer)
		{
			if (xplayer->inventory2.GetNumItemsInCategory() <= xplayer->GetMaxInvWeight() &&
				xplayer->HasBuff("STRETCH") == nullptr)
				return THISCALL(Ivk_oCAIHuman_SpecialMove)(pressed);
		}

		return FALSE;
	}

	void oCZoneMusic::ProcessZoneList_Mod(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld)
	{
		zBOOL daytimeChanged = FALSE;
		zBOOL herostatusChanged = FALSE;

		zBOOL daytime = IsDaytime();
		oHEROSTATUS herostatus = GetHerostatus();

		if (s_daytime != daytime)
		{
			daytimeChanged = TRUE;
		}

		if (s_herostatus != herostatus)
		{
			herostatusChanged = TRUE;
		}

		THISCALL(Ivk_oCZoneMusic_ProcessZoneList)(zoneList, zoneDeactivateList, homeWorld);

		zSTRING newTheme;
		GetNewTheme(&newTheme);

		if (daytimeChanged || herostatusChanged)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				if (newTheme.Search("NCI_", 1U) != -1 || newTheme.Search("NCO_", 1U) != -1)
				{
					xplayer->SetWinterZone(true);
				}
				else
				{
					xplayer->SetWinterZone(false);
				}
			}
		}
	}
}