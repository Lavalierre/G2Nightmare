// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {

	class xGameController
	{
	public:

		xGameController(const xGameController&) = delete;
		xGameController& operator=(xGameController&) = delete;
		static xGameController& GetInstance() { return oInstance; }

		void Init();
		void Process();
		void ProcessBuffsUI();

		void DefineExternals();

		void AddBuffArch(string type, string name, string startFX = "NULL", string tickFX = "NULL", string endFX = "NULL");
		BuffArch* GetBuffArch(string type);

		void AddHeavyArmor(string instance);
		bool IsArmorHeavy(string instance);

		oCViewStatusBar* invBar = nullptr;
		oCViewStatusBar* toxicBar = nullptr;

	private:

		xGameController() = default;
		static xGameController oInstance;

		int timerSecs = 0;

		std::map<string, BuffArch*> vBuffTypes;
		std::vector<string> vHeavyArmor;
	};
}