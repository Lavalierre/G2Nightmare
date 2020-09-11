// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	
	void xNpc::OnBuffApplied(PlayerBuff* buff)
	{

		// BURNING

		if (buff->type == "BURNING")
		{
			if (HasLongBuff("FIREDRAGONBUFF"))
			{
				fireDragonBuffHP = int(GetAttribute(NPC_ATR_HITPOINTSMAX) / 2);
				ChangeAttribute(NPC_ATR_HITPOINTSMAX, -fireDragonBuffHP);
			}
		}

		// WET

		if (buff->type == "WET")
		{
			if (HasLongBuff("ICEDRAGONBUFF") != nullptr)
			{
				if (buff->infinite == true)
					AddLongBuff("FREEZE");
				else
					AddBuff("FREEZE", buff->duration);
			}
		}

		// STRETCH

		if (buff->type == "STRETCH")
		{
			if (HasLongBuff("SWAMPDRAGONBUFF"))
			{
				int hitpoints = GetAttribute(NPC_ATR_HITPOINTS) - 50;
				if (human_ai->wmode == NPC_WEAPON_NONE)
				{
					RemoveFromSlot(NPC_NODE_RIGHTHAND, FALSE, FALSE);
					RemoveFromSlot(NPC_NODE_LEFTHAND, FALSE, FALSE);
					SetInteractItem(NULL);
				}
				DropUnconscious(100, enemy);
				SetAttribute(NPC_ATR_HITPOINTS, hitpoints);
			}
		}

		// TOXIC

		if (buff->type == "TOXIC" && GetBodyState() != BS_UNCONSCIOUS)
		{
			int hitpoints = GetAttribute(NPC_ATR_HITPOINTS);
			int decreaseHealth = (GetAttribute(NPC_ATR_HITPOINTSMAX) / 100) * 15;	// 15%
			if (GetSlotItem(NPC_NODE_RIGHTHAND) || GetSlotItem(NPC_NODE_LEFTHAND))
			{
				if (human_ai->wmode <= NPC_WEAPON_DAG)
				{
					RemoveFromSlot(NPC_NODE_RIGHTHAND, FALSE, FALSE);
					RemoveFromSlot(NPC_NODE_LEFTHAND, FALSE, FALSE);
					SetInteractItem(NULL);
				}
			}
			DropUnconscious(100, enemy);
			SetAttribute(NPC_ATR_HITPOINTS, hitpoints);
			ChangeAttribute(NPC_ATR_HITPOINTS, -decreaseHealth);
		}

		// ROCK DRAGON BUFF

		if (buff->type == "ROCKDRAGONBUFF")
		{
			maxInvWeight -= 35;
		}

		// *** POTIONS *** //

		// INVISIBILITY //

		if (buff->type == "INVISIBILITY" && showVisual != FALSE)
		{
			showVisual = FALSE;
		}

		// FIRERESIST

		if (buff->type == "FIRERESIST")
		{
			maxInvWeight -= 30;
		}

		// ENRAGE

		if (buff->type == "ENRAGE")
		{
			for (int i = 0; i < oEDamageIndex_MAX; i++)
			{
				enrageProtection[i] += protection[i];
				protection[i] -= protection[i];

				ApplyOverlay("HUMANS_SPRINT.MDS");
			}
		}

		// STRENGTH

		if (buff->type == "STRENGTH")
		{
			maxInvWeight += 20;
		}
	}
	void xNpc::OnBuffDispelled(PlayerBuff* buff)
	{

		// BURNING

		if (buff->type == "BURNING")
		{
			if (HasLongBuff("FIREDRAGONBUFF") || fireDragonBuffHP != 0)
			{
				ChangeAttribute(NPC_ATR_HITPOINTSMAX, fireDragonBuffHP);
				fireDragonBuffHP = 0;
			}
		}

		// TOXIC

		if (buff->type == "TOXIC")
		{
			if (!IsDead())
			{
				state.ClearAIState();
				StandUp(FALSE, TRUE);
			}
		}

		// STRETCH

		if (buff->type == "STRETCH")
		{
			if (IsUnconscious())
			{
				if (!IsDead())
				{
					state.ClearAIState();
					StandUp(FALSE, TRUE);
				}
			}
		}

		// ROCK DRAGON BUFF

		if (buff->type == "ROCKDRAGONBUFF")
		{
			maxInvWeight += 35;
		}

		// *** POTIONS *** //

		// INVISIBILITY

		if (buff->type == "INVISIBILITY")
		{
			showVisual = TRUE;
		}

		// FIRERESIST

		if (buff->type == "FIRERESIST")
		{
			maxInvWeight += 30;
		}

		// ENRAGE

		if (buff->type == "ENRAGE")
		{
			for (int i = 0; i < oEDamageIndex_MAX; i++)
			{
				protection[i] += enrageProtection[i];
				enrageProtection[i] = 0;

				RemoveOverlay("HUMANS_SPRINT.MDS");
			}
		}

		// STRENGTH

		if (buff->type == "STRENGTH")
		{
			maxInvWeight -= 20;
		}
	}

	void xNpc::OnBuffTicks(PlayerBuff* buff)
	{
		// BURNING

		if (buff->type == "BURNING")
		{
			if (HasLongBuff("WEAK"))
			{
				GetEM(0)->OnDamage(this, this, buff->damagePerSec * 2, buff->damageType, GetAtVectorWorld());
			}
			else
			{
				GetEM(0)->OnDamage(this, this, buff->damagePerSec, buff->damageType, GetAtVectorWorld());
			}
		}

		// BLEEDING

		if (buff->type == "BLEEDING")
		{
			if (!human_ai->IsStanding())
			{
				GetEM(0)->OnDamage(this, this, buff->damagePerSec, buff->damageType, GetAtVectorWorld());
			}
		}

		// WET

		if (buff->type == "WET")
		{
			if (HasBuff("FREEZE") || HasLongBuff("FREEZE"))
			{
				if (!human_ai->IsStanding())
				{
					GetEM(0)->OnDamage(this, this, buff->damagePerSec, buff->damageType, GetAtVectorWorld());
				}
			}
		}

		// TOXIC

		if (buff->type == "TOXIC" && GetBodyState() != BS_UNCONSCIOUS)
		{
			int hitpoints = GetAttribute(NPC_ATR_HITPOINTS);
			DropUnconscious(100, enemy);
			SetAttribute(NPC_ATR_HITPOINTS, hitpoints);
		}

		// *** POTIONS *** //

		// INVISIBILITY //

		if (buff->type == "INVISIBILITY" && showVisual != FALSE)
		{
			showVisual = FALSE;
		}

		// ENRAGE //

		if (buff->type == "ENRAGE" && !GetModel()->HasAppliedModelProtoOverlay("HUMANS_SPRINT.MDS"))
		{
			ApplyOverlay("HUMANS_SPRINT.MDS");
		}
	}

}