class CfgPatches
{
	class AlbtrauminselAIVoice
	{
		requiredVersion = 0.1;
		units[] = {};
		requiredAddons[] =
			{
				"DZ_Data",
				"DZ_Scripts",
				"DayZExpansion_Core_Scripts"};
	};
};

class CfgMods
{
	class AlbtrauminselAIVoice
	{
		dir = "AlbtrauminselAIVoice";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Expansion AI - PersonalRadio Notice";
		credits = "";
		author = "KOMA";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"AlbtrauminselAIVoice/scripts/3_game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"AlbtrauminselAIVoice/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"AlbtrauminselAIVoice/scripts/5_mission"};
			};
		};
	};
};

class CfgSoundShaders
{
	class AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {};
		frequency = 1;
		range = 25;
		volume = 0.8;
	};
	class PersonalRadio_Zelenogorsk_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Zelenogorsk_Mercenaries", 1}};
	};
	class PersonalRadio_Zelenogorsk_East_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Zelenogorsk_East", 1}};
	};
	class PersonalRadio_Metalurg_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Metalurg_Mercenaries", 1}};
	};
	class PersonalRadio_Metalurg_East_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Metalurg_East", 1}};
	};
	class PersonalRadio_Stary_Sobor_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Stary_Sobor_Mercenaries", 1}};
	};
	class PersonalRadio_Stary_Sobor_East_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Stary_Sobor_East", 1}};
	};
	class PersonalRadio_Unknown_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Unknown", 1}};
	};
}

class CfgSoundSets
{
	class PersonalRadio_Zelenogorsk_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Zelenogorsk_Mercenaries_SoundShader"};
	};
	class PersonalRadio_Zelenogorsk_East_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Zelenogorsk_East_SoundShader"};
	};
	class PersonalRadio_Metalurg_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Metalurg_Mercenaries_SoundShader"};
	};
	class PersonalRadio_Metalurg_East_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Metalurg_East_SoundShader"};
	};
	class PersonalRadio_Stary_Sobor_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Stary_Sobor_Mercenaries_SoundShader"};
	};
	class PersonalRadio_Stary_Sobor_East_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Stary_Sobor_East_SoundShader"};
	};
	class PersonalRadio_Unknown_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Unknown_SoundShader"};
	};
};
