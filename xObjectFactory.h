// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
	
	class xObjectFactory : public oCObjectFactory
	{
	public:

		zCLASS_UNION_DECLARATION(xObjectFactory);

		virtual oCNpc* CreateNpc(int idx);

	private:
	};
}