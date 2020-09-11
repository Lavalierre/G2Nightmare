// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	
	zCLASS_UNION_DEFINITION(xNpc, oCNpc, 0, 0);

	void xNpc::AddToxic(float amount)
	{
		toxic += amount;

		if (GetToxic() >= GetMaxToxic())
		{
			toxic = GetMaxToxic();
			AddBuff("TOXIC", 7000);
		}
	}

	void xNpc::AddDesease()
	{
		if (GetAttribute(NPC_ATR_HITPOINTSMAX) > 10)
		{
			deseaseLevel += 1;
			ChangeAttribute(NPC_ATR_HITPOINTSMAX, -10);
		}
	}

	void xNpc::ClearDesease()
	{
		if (deseaseLevel != 0)
		{
			ChangeAttribute(NPC_ATR_HITPOINTSMAX, (deseaseLevel * 10));
			deseaseLevel = 0;
			DeleteLongBuff("DESEASE");
		}
	}

	void xNpc::Archive(zCArchiver& arc)
	{
		oCNpc::Archive(arc);

		arc.WriteFloat("toxic", toxic);
		arc.WriteInt("maxInvWeight", maxInvWeight);
		arc.WriteInt("deseaseLevel", deseaseLevel);
		arc.WriteInt("fireDragonBuffHP", fireDragonBuffHP);
		arc.WriteRaw("enrageProtection", enrageProtection, sizeof(enrageProtection));

		arc.WriteInt("numBuffs", vBuffs.size());

		for (int i = 0; i < vBuffs.size(); i++)
		{
			arc.WriteObject(vBuffs[i]);
		}

	}

	void xNpc::Unarchive(zCArchiver& arc)
	{
		oCNpc::Unarchive(arc);

		PlayerBuff* newBuff;
		int numBuffs;

		arc.ReadFloat("toxic", toxic);
		arc.ReadInt("maxInvWeight", maxInvWeight);
		arc.ReadInt("deseaseLevel", deseaseLevel);
		arc.ReadInt("fireDragonBuffHP", fireDragonBuffHP);
		arc.ReadRaw("enrageProtection", enrageProtection, sizeof(enrageProtection));

		arc.ReadInt("numBuffs", numBuffs);

		ClearBuffList();
		ClearLongBuffs();
		ClearPermanentBuffs();

		for (int i = 0; i < numBuffs; i++)
		{
			newBuff = dynamic_cast<PlayerBuff*>(arc.ReadObjectAccount(__FILE__, __LINE__, NULL));
			if (newBuff)
			{
				AddBuff(newBuff);
			}
		}

	}

	// *** PROCESSING *** //

	void xNpc::ProcessNpc()
	{
		oCNpc::ProcessNpc();

		if (IsAPlayer())
		{
			// Inventory overweight - light

			if (inventory2.GetNumItemsInCategory() > GetMaxInvWeight())
			{
				if (human_ai->walkmode != ANI_WALKMODE_WALK && human_ai->CanToggleWalkModeTo(ANI_WALKMODE_WALK))
				{
					human_ai->ToggleWalkMode(-1);
				}

				if (GetWalkStopChasm() == TRUE)
					SetWalkStopChasm(FALSE);
			}

			// Inventory overweight - hard

			static int hpDamageTimer = 0;
			const int hpDamageTimerMax = 1000;
			const int hpDamage = 1;

			if (inventory2.GetNumItemsInCategory() > (GetMaxInvWeight() + 10))
			{
				if (!human_ai->IsStanding())
				{
					hpDamageTimer += ztimer->frameTime / ztimer->factorMotion;

					if (hpDamageTimer >= hpDamageTimerMax)
					{
						hpDamageTimer = 0;
						SetAttribute(NPC_ATR_HITPOINTS, GetAttribute(NPC_ATR_HITPOINTS) - hpDamage);

						if (GetAttribute(NPC_ATR_HITPOINTS) <= 0)
							DoDie(this);
					}
				}
			}
			else
			{
				if (hpDamageTimer != 0)
					hpDamageTimer = 0;
			}

			// Slowness debuffs

			if (HasBuff("INVISIBILITY") != nullptr ||
				HasBuff("STRETCH") != nullptr ||
				HasBuff("FREEZE") != nullptr ||
				HasLongBuff("FREEZE") != nullptr)
			{
				if (human_ai->walkmode != ANI_WALKMODE_WALK && human_ai->CanToggleWalkModeTo(ANI_WALKMODE_WALK))
				{
					human_ai->ToggleWalkMode(-1);
				}

				if (GetWalkStopChasm() == TRUE)
					SetWalkStopChasm(FALSE);
			}

			// Processing player buffs

			if (!ogame->singleStep)
				ProcessBuffs();
		}

		//
	}

	void xNpc::ProcessBuffs()
	{
		// Applying buffs
		
		ClearLongBuffs();

		for (int i = 0; i < vobList.GetNumInList(); i++)
		{
			oCNpc* targetNpc = dynamic_cast<oCNpc*>(vobList[i]);
			if (targetNpc)
			{
				if (GetDistanceToVob(*vobList[i]) <= 200)
				{
					zSTRING instance = targetNpc->GetInstanceName().Upper();
					if (instance == "SWAMPGOLEM" ||
						instance == "SWAMPGOLEM_VALLEY" ||
						instance == "SWAMPDRONE")
					{
						AddToxic((ztimer->frameTime / ztimer->factorMotion) / 25);
					}

					if (instance == "FIREGOLEM" ||
						instance == "SHADOWBEAST_ADDON_FIRE" ||
						instance == "SHADOWBEAST_ADDON_FIRE_CANYONLIB")
					{
						AddBuff("BURNING", 5000, 0, 5, oEDamageType_Fire);
						AddBuff("WARM", 5000);
					}

					if (instance == "ICEGOLEM" ||
						instance == "ICEGOLEM_SYLVIO1" ||
						instance == "ICEGOLEM_SYLVIO2")
					{
						AddBuff("FREEZE", 8000, 0, 0, oEDamageType_Magic);
					}
				}
			}
			if (vobList[i] && vobList[i]->visual && vobList[i]->visual->GetVisualName())
			{
				if (vobList[i]->visual->GetVisualName() == "FIRE.pfx" ||
					vobList[i]->visual->GetVisualName() == "FIRE_HOT.pfx")
				{
					if (GetDistanceToVob(*vobList[i]) <= 350)
					{
						AddLongBuff("WARM");
					}

					if (GetDistanceToVob(*vobList[i]) <= 125)
					{
						AddBuff("BURNING", 5000, 0, 5, oEDamageType_Fire);
						AddBuff("WARM", 5000);
					}
				}

				if (vobList[i]->visual->GetVisualName() == "LAVAFOG_BIG.pfx")
				{
					if (GetDistanceToVob(*vobList[i]) <= 8000)
					{
						AddLongBuff("WEAK");
					}
				}
			}
		}

		// DESEASE

		if (deseaseLevel != 0)
		{
			AddLongBuff("DESEASE");
		}

		// WET BUFF

		const zVEC3 playerPos = player->GetPositionWorld();
		const zVEC3 rayPos = zVEC3(playerPos[0], playerPos[1] + 50000.0f, playerPos[2]);
		zCSkyControler_Outdoor* skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(GetHomeWorld()->GetActiveSkyControler());

		if (anictrl->GetWaterLevel() != 0)
		{
			AddLongBuff("WET", 0, 5);
		}
		else if (skyCtrl && skyCtrl->rainFX.outdoorRainFXWeight > 0.3f && skyCtrl->GetWeatherType() == zTWEATHER_RAIN)
		{
			if (!player->GetHomeWorld()->TraceRayNearestHit(playerPos, rayPos, (zCVob*)0, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE | zTRACERAY_POLY_IGNORE_TRANSP))
			{
				AddLongBuff("WET", 0, 5);
			}
		}

		// WINTER ZONE

		if (IsWinterZone())
		{
			AddLongBuff("FREEZE");
		}

		// STRETCH BUFF

		if (GetModel()->isFlying)
		{
			if (anictrl->fallDownDistanceY >= 300.0f)
			{
				if (anictrl->aboveFloor < 10)
				{
					if (!GetTalentSkill(oCNpcTalent::NPC_TAL_ACROBAT) || HasBuff("ROCKDRAGONBUFF"))
					{
						AddBuff("STRETCH", 5000);
					}
				}
			}
		}

		// Processing toxic

		if (toxic > 0)
		{
			toxic -= (ztimer->frameTime / ztimer->factorMotion) / 20;
			if (toxic < 0)
				toxic = 0;
		}

		// Buff colliding

		if (HasBuff("FREEZE") || HasLongBuff("FREEZE") ||
			HasBuff("WET") || HasLongBuff("WET"))
		{
			DeleteBuff("BURNING");
			DeleteLongBuff("BURNING");
		}

		if (HasBuff("WARM") || HasLongBuff("WARM"))
		{
			DeleteBuff("FREEZE");
			DeleteLongBuff("FREEZE");
			DeleteBuff("WET");
			DeleteLongBuff("WET");
		}

		// Processing buffs

		PlayerBuff* buff;

		for (auto it = vBuffs.begin(); it != vBuffs.end();)
		{

			buff = *it;
			buff->dmgTick += ztimer->frameTime / ztimer->factorMotion;
			// Processing time

			if (buff && buff->infinite == false)
			{
				buff->duration -= ztimer->frameTime / ztimer->factorMotion;
				if ((buff->duration / 1000) <= 0)
				{
					DeleteBuff(*it);
					continue;
				}
			}

			// Processing periodic damage
			if (buff->dmgTick >= 1000)
			{
				if (buff->archType->tickFX != "NULL")
				{
					zSTRING ID(buff->archType->tickFX);
					zSTRING levelID = buff->archType->tickFX + "_L1";
					if (oCVisualFX::fxParser->GetSymbol(levelID))
						ID = levelID;

					buff->visFX->Stop(0);
					buff->visFX->SetByScript(ID);
					buff->visFX->Init(this, this, NULL);
					buff->visFX->Cast(1);
				}

				OnBuffTicks(buff);
				buff->dmgTick = 0;
			}
			
			it++;
		}
	}
}