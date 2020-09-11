// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE 
{
	class BuffArch
	{
	public:
		string name;
		string startFX;
		string endFX;
		string tickFX;
	};

	class PlayerBuff : public zCObject
	{
	public:
		zCLASS_UNION_DECLARATION(PlayerBuff);
		string type;
		BuffArch* archType;
		int damage;
		int damagePerSec;
		int damageType;
		int dmgTick;
		int duration;
		bool dispellable;
		bool infinite;
		bool permanent;
		oCVisualFX* visFX;

		virtual void Archive(zCArchiver& arc);
		virtual void Unarchive(zCArchiver& arc);
	};

	zCLASS_UNION_DEFINITION(PlayerBuff, zCObject, 0, 0);

	void PlayerBuff::Archive(zCArchiver& arc)
	{
		zCObject::Archive(arc);

		arc.WriteString("type", type.ToChar());
		arc.WriteInt("damage", damage);
		arc.WriteInt("damagePerSec", damagePerSec);
		arc.WriteInt("damageType", damageType);
		arc.WriteInt("dmgTick", dmgTick);
		arc.WriteInt("duration", duration);
		arc.WriteInt("infinite", infinite);
		arc.WriteInt("permanent", permanent);
	}

	void PlayerBuff::Unarchive(zCArchiver& arc)
	{
		zCObject::Unarchive(arc);

		zSTRING buffType = "";
		int infBool, permBool;
		arc.ReadString("type", buffType);
		arc.ReadInt("damage", damage);
		arc.ReadInt("damagePerSec", damagePerSec);
		arc.ReadInt("damageType", damageType);
		arc.ReadInt("dmgTick", dmgTick);
		arc.ReadInt("duration", duration);
		arc.ReadInt("infinite", infBool);
		arc.ReadInt("infinite", permBool);

		type = buffType.ToChar();
		infinite = infBool;
		permanent = permBool;
	}
}