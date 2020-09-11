// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {

	zBOOL Mod_AddBuff_Invisibility()
	{
		zCParser* p = zCParser::GetParser();
		int nTicks;

		p->GetParameter(nTicks);

		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->AddBuff("INVISIBILITY", nTicks, 0, 5, oEDamageType_Fire);
				return TRUE;
			}
		}
	}

	zBOOL Mod_AddBuff_FireResistance()
	{
		zCParser* p = zCParser::GetParser();
		int nTicks;

		p->GetParameter(nTicks);

		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->AddBuff("FIRERESIST", nTicks, 0, 5, oEDamageType_Fire);
				return TRUE;
			}
		}
	}

	zBOOL Mod_AddBuff_Enrage()
	{
		zCParser* p = zCParser::GetParser();
		int nTicks;

		p->GetParameter(nTicks);

		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->AddBuff("ENRAGE", nTicks, 0, 5, oEDamageType_Fire);
				return TRUE;
			}
		}
	}

	zBOOL Mod_AddBuff_Strength()
	{
		zCParser* p = zCParser::GetParser();
		int nTicks;

		p->GetParameter(nTicks);

		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->AddBuff("STRENGTH", nTicks, 0, 5, oEDamageType_Fire);
				return TRUE;
			}
		}
	}

	zBOOL Mod_AddBuff_Burn()
	{
		zCParser* p = zCParser::GetParser();
		int nTicks;

		p->GetParameter(nTicks);

		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->AddBuff("BURNING", nTicks, 0, 5, oEDamageType_Fire);
				xplayer->AddBuff("WARM", nTicks);
				return TRUE;
			}
		}
	}

	zBOOL Mod_AddToxic()
	{
		zCParser* p = zCParser::GetParser();
		int nToxic;

		p->GetParameter(nToxic);

		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->AddToxic(nToxic);
				return TRUE;
			}
		}

		return FALSE;
	}

	zBOOL Mod_ClearDesease()
	{
		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				xplayer->ClearDesease();
				return TRUE;
			}
		}

		return FALSE;
	}

	zBOOL Mod_TryingToTeleport()
	{
		if (player)
		{
			xNpc* xplayer = dynamic_cast<xNpc*>(player);
			if (xplayer)
			{
				if (xplayer->HasBuff("STRENGTH") != nullptr)
				{
					if (xplayer->inventory2.GetNumItemsInCategory() >= (xplayer->GetMaxInvWeight() - 10))
					{
						float nDamage = (xplayer->GetAttribute(NPC_ATR_HITPOINTS) / 100.0f) * 30;	// 30%
						xplayer->ChangeAttribute(NPC_ATR_HITPOINTS, -nDamage);
					}
				}
				else if (xplayer->inventory2.GetNumItemsInCategory() >= (xplayer->GetMaxInvWeight() + 20))
				{
					float nDamage = (xplayer->GetAttribute(NPC_ATR_HITPOINTS) / 100.0f) * 30;	// 30%
					xplayer->ChangeAttribute(NPC_ATR_HITPOINTS, -nDamage);
				}

				return TRUE;
			}
		}

		return FALSE;
	}
}