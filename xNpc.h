// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {

	class xNpc : public oCNpc
	{
	public:

		zCLASS_UNION_DECLARATION(xNpc);

		virtual void ProcessNpc();
		virtual void Archive(zCArchiver& arc);
		virtual void Unarchive(zCArchiver& arc);
		void ProcessBuffs();


		// Buffs
		std::vector<PlayerBuff*> GetBuffList() { return vBuffs; }
		void ClearBuffList();
		void ClearLongBuffs();
		void ClearPermanentBuffs();
		void AddBuff(PlayerBuff* buff);
		void AddBuff(string type, int duration, int damage = 0, int damagePerSec = 0, int damageType = oEDamageType_Magic);
		void AddLongBuff(string type, int damage = 0, int damagePerSec = 0, int damageType = oEDamageType_Magic, bool permanent = false);

		PlayerBuff* HasBuff(string type);
		PlayerBuff* HasLongBuff(string type);

		void DeleteBuff(PlayerBuff* buff);
		void DeleteBuff(string type);
		void DeleteLongBuff(string type);

		void OnBuffApplied(PlayerBuff* buff);
		void OnBuffDispelled(PlayerBuff* buff);
		void OnBuffTicks(PlayerBuff* buff);

		void AddToxic(float amount);
		int GetToxic() const { return toxic; }
		int GetMaxToxic() const { return toxicMax; }

		void AddDesease();
		void ClearDesease();
		bool IsDesease() const { return deseaseLevel != 0; }
		int GetDeseaseLevel() const { return deseaseLevel; }
		void SetDeseaseLevel(int lvl) { deseaseLevel = lvl; }

		void	SetMaxInvWeight(int weight)		{ maxInvWeight = weight; }
		int		GetMaxInvWeight()				{ return maxInvWeight; }

		void	SetWinterZone(bool toggle)		{ bWinterZone = toggle; }
		bool	IsWinterZone()					{ return bWinterZone; }

	private:

		std::vector<PlayerBuff*> vBuffs;

		// Potions
		int enrageProtection[oEDamageIndex_MAX];
		float toxic = 0.0f;
		float toxicMax = 1000.0f;

		int maxInvWeight = 70;
		int deseaseLevel = 0;

		bool bWinterZone = false;

		int fireDragonBuffHP = 0;
	};
}