// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	
	void xNpc::AddBuff(PlayerBuff* buff)
	{
		vBuffs.push_back(buff);
		buff->archType = xGameController::GetInstance().GetBuffArch(buff->type);

		buff->visFX = new oCVisualFX();
		buff->visFX->SetIsProjectile(FALSE);
		buff->visFX->root = buff->visFX;
		buff->visFX->parent = buff->visFX;

		zSTRING ID(buff->archType->startFX);
		zSTRING levelID = buff->archType->startFX + "_L1";
		if (oCVisualFX::fxParser->GetSymbol(levelID))
			ID = levelID;

		buff->visFX->SetByScript(ID);
		buff->visFX->SetDamage(0);
		buff->visFX->SetDamageType(0);
		buff->visFX->SetLevel(0, 0);
		
		if (buff->archType->startFX != "NULL")
		{
			zSTRING ID(buff->archType->startFX);
			zSTRING levelID = buff->archType->startFX + "_L1";
			if (oCVisualFX::fxParser->GetSymbol(levelID))
				ID = levelID;

			buff->visFX->SetByScript(ID);
			buff->visFX->Init(this, this, NULL);
			buff->visFX->Cast(1);
		}
	}

	void xNpc::AddBuff(string name, int duration, int dmg, int dmgsec, int dmgtype)
	{
		PlayerBuff* buffExist = HasBuff(name);
		if (buffExist == nullptr)
		{
			PlayerBuff* newbuff = new PlayerBuff;
			newbuff->type = name;
			newbuff->archType = xGameController::GetInstance().GetBuffArch(newbuff->type);
			newbuff->duration = duration;
			newbuff->damage = dmg;
			newbuff->damageType = dmgtype;
			newbuff->dmgTick = 0;
			newbuff->damagePerSec = dmgsec;
			newbuff->infinite = false;
			newbuff->visFX = nullptr;

			newbuff->visFX = new oCVisualFX();
			newbuff->visFX->SetIsProjectile(FALSE);
			newbuff->visFX->root = newbuff->visFX;
			newbuff->visFX->parent = newbuff->visFX;

			zSTRING ID(newbuff->archType->startFX);
			zSTRING levelID = newbuff->archType->startFX + "_L1";
			if (oCVisualFX::fxParser->GetSymbol(levelID))
				ID = levelID;

			newbuff->visFX->SetByScript(ID);
			newbuff->visFX->SetDamage(0);
			newbuff->visFX->SetDamageType(0);
			newbuff->visFX->SetLevel(0, 0);

			if (newbuff->archType->startFX != "NULL")
			{
				zSTRING ID(newbuff->archType->startFX);
				zSTRING levelID = newbuff->archType->startFX + "_L1";
				if (oCVisualFX::fxParser->GetSymbol(levelID))
					ID = levelID;

				newbuff->visFX->SetByScript(ID);
				newbuff->visFX->Init(this, this, NULL);
				newbuff->visFX->Cast(1);
			}

			vBuffs.push_back(newbuff);
			OnBuffApplied(newbuff);
		}
		else
		{
			buffExist->duration = duration;
			buffExist->damage = dmg;
			buffExist->damagePerSec = dmgsec;
		}
	}

	void xNpc::AddLongBuff(string name, int dmg, int dmgsec, int dmgtype, bool permanent)
	{
		PlayerBuff* buffExist = HasLongBuff(name);
		if (buffExist == nullptr)
		{
			PlayerBuff* newbuff = new PlayerBuff;
			newbuff->type = name;
			newbuff->archType = xGameController::GetInstance().GetBuffArch(newbuff->type);
			newbuff->damage = dmg;
			newbuff->damagePerSec = dmgsec;
			newbuff->damageType = dmgtype;
			newbuff->dmgTick = 0;
			newbuff->visFX = nullptr;
			newbuff->infinite = true;
			newbuff->permanent = permanent;

			newbuff->visFX = new oCVisualFX();
			newbuff->visFX->SetIsProjectile(FALSE);
			newbuff->visFX->root = newbuff->visFX;
			newbuff->visFX->parent = newbuff->visFX;

			zSTRING ID(newbuff->archType->startFX);
			zSTRING levelID = newbuff->archType->startFX + "_L1";
			if (oCVisualFX::fxParser->GetSymbol(levelID))
				ID = levelID;

			newbuff->visFX->SetByScript(ID);
			newbuff->visFX->SetDamage(0);
			newbuff->visFX->SetDamageType(0);
			newbuff->visFX->SetLevel(0, 0);

			if (newbuff->archType->startFX != "NULL")
			{
				zSTRING ID(newbuff->archType->startFX);
				zSTRING levelID = newbuff->archType->startFX + "_L1";
				if (oCVisualFX::fxParser->GetSymbol(levelID))
					ID = levelID;

				newbuff->visFX->SetByScript(ID);
				newbuff->visFX->Init(this, this, NULL);
				newbuff->visFX->Cast(1);
			}

			vBuffs.push_back(newbuff);
			OnBuffApplied(newbuff);
		}
	}

	PlayerBuff* xNpc::HasBuff(string name)
	{
		for (PlayerBuff* buff : vBuffs)
		{
			if (buff->type == name && buff->infinite == false)
				return buff;
		}

		return nullptr;
	}

	PlayerBuff* xNpc::HasLongBuff(string name)
	{
		for (PlayerBuff* buff : vBuffs)
		{
			if (buff->type == name && buff->infinite == true)
				return buff;
		}

		return nullptr;
	}

	void xNpc::ClearBuffList()
	{
		for (auto it = vBuffs.begin(); it != vBuffs.end(); it++)
		{
			if ((*it)->visFX != nullptr)
			{
				(*it)->visFX->Stop(1);
				(*it)->visFX->Release();
			}
			OnBuffDispelled(*it);
			(*it)->Release();
		}

		vBuffs.clear();
	}

	void xNpc::ClearLongBuffs()
	{
		for (auto it = vBuffs.begin(); it != vBuffs.end();)
		{
			if ((*it)->infinite == true && (*it)->permanent == false)
			{
				if ((*it)->visFX != nullptr)
				{
					(*it)->visFX->Stop(1);
					(*it)->visFX->Release();
				}
				OnBuffDispelled(*it);
				(*it)->Release();
				vBuffs.erase(it);
			}
			else
				it++;
		}
	}

	void xNpc::ClearPermanentBuffs()
	{
		for (auto it = vBuffs.begin(); it != vBuffs.end();)
		{
			if ((*it)->infinite == true && (*it)->permanent == true)
			{
				if ((*it)->visFX != nullptr)
				{
					(*it)->visFX->Stop(1);
					(*it)->visFX->Release();
				}
				OnBuffDispelled(*it);
				(*it)->Release();
				vBuffs.erase(it);
			}
			else
				it++;
		}
	}

	void xNpc::DeleteBuff(PlayerBuff* buff)
	{
		for (auto it = vBuffs.begin(); it != vBuffs.end(); it++)
		{
			if ((*it) == buff)
			{

				if (buff->visFX)
				{
					buff->visFX->Stop(1);
					buff->visFX->Release();
				}

				OnBuffDispelled(buff);

				buff->Release();
				vBuffs.erase(it);
				break;
			}
		}
	}

	// 

	void xNpc::DeleteBuff(string type)
	{
		for (auto it = vBuffs.begin(); it != vBuffs.end(); it++)
		{
			if ((*it)->type == type && (*it)->infinite == false)
			{
				PlayerBuff* buff = *it;

				if (buff->visFX)
				{
					buff->visFX->Stop(1);
					buff->visFX->Release();
				}

				OnBuffDispelled(buff);

				buff->Release();
				vBuffs.erase(it);
				break;
			}
		}
	}

	void xNpc::DeleteLongBuff(string type)
	{
		for (auto it = vBuffs.begin(); it != vBuffs.end(); it++)
		{
			if ((*it)->type == type && (*it)->infinite == true)
			{
				PlayerBuff* buff = *it;

				if ((*it)->visFX != nullptr)
				{
					buff->visFX->Stop(1);
					buff->visFX->Release();
				}

				OnBuffDispelled(buff);

				buff->Release();
				vBuffs.erase(it);
				break;
			}
		}
	}

}