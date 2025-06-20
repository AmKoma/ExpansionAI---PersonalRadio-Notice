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

class CfgVehicles
{
	class PersonalRadio
	{
		class EnergyManager
		{
			hasIcon = 1;
			autoSwitchOff = 1;
			energyUsagePerSecond = 0.001;
			plugType = 1;
			attachmentAction = 1;
			wetnessExposure = 0.1;
		};
	}
}

class CfgSoundShaders
{
	class AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {};
		frequency = 1;
		range = 25;
		volume = 0.8;
	};
	class PersonalRadio_Airfield_Vybor_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Airfield_Vybor_Mercenaries", 1}};
	};

	class PersonalRadio_Balota_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Balota_Mercenaries", 1}};
	};

	class PersonalRadio_Bolshoy_Kotel_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Bolshoy_Kotel_Mercenaries", 1}};
	};

	class PersonalRadio_Chernaya_Polyana_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Chernaya_Polyana_Mercenaries", 1}};
	};

	class PersonalRadio_Chernogorsk_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Chernogorsk_Mercenaries", 1}};
	};

	class PersonalRadio_Elektrozavodsk_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Elektrozavodsk_Mercenaries", 1}};
	};

	class PersonalRadio_Gorka_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Gorka_Mercenaries", 1}};
	};

	class PersonalRadio_Krasnostav_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Krasnostav_Mercenaries", 1}};
	};

	class PersonalRadio_Metalurg_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Metalurg_Mercenaries", 1}};
	};

	class PersonalRadio_Nadezhdino_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Nadezhdino_Mercenaries", 1}};
	};

	class PersonalRadio_Novaya_Petrovka_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Novaya_Petrovka_Mercenaries", 1}};
	};

	class PersonalRadio_Novodmitrovsk_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Novodmitrovsk_Mercenaries", 1}};
	};

	class PersonalRadio_Novy_Sobor_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Novy_Sobor_Mercenaries", 1}};
	};

	class PersonalRadio_Polyana_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Polyana_Mercenaries", 1}};
	};

	class PersonalRadio_Rogovo_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Rogovo_Mercenaries", 1}};
	};

	class PersonalRadio_Severograd_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Severograd_Mercenaries", 1}};
	};

	class PersonalRadio_Sosnovka_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Sosnovka_Mercenaries", 1}};
	};

	class PersonalRadio_Stary_Sobor_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Stary_Sobor_Mercenaries", 1}};
	};

	class PersonalRadio_Unknown_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Unknown", 1}};
	};

	class PersonalRadio_Vybor_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Vybor_Mercenaries", 1}};
	};

	class PersonalRadio_Vyshnoye_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Vyshnoye_Mercenaries", 1}};
	};

	class PersonalRadio_Zelenogorsk_Mercenaries_SoundShader : AlbtrauminselAIVoice_SoundShaderBase
	{
		samples[] = {{"AlbtrauminselAIVoice\Audio\PersonalRadio_Zelenogorsk_Mercenaries", 1}};
	};
};

class CfgSoundSets
{
	class PersonalRadio_Airfield_Vybor_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Airfield_Vybor_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Balota_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Balota_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Bolshoy_Kotel_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Bolshoy_Kotel_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Chernaya_Polyana_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Chernaya_Polyana_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Chernogorsk_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Chernogorsk_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Elektrozavodsk_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Elektrozavodsk_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Gorka_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Gorka_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Krasnostav_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Krasnostav_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Metalurg_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Metalurg_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Nadezhdino_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Nadezhdino_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Novaya_Petrovka_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Novaya_Petrovka_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Novodmitrovsk_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Novodmitrovsk_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Novy_Sobor_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Novy_Sobor_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Polyana_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Polyana_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Rogovo_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Rogovo_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Severograd_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Severograd_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Sosnovka_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Sosnovka_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Stary_Sobor_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Stary_Sobor_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Unknown_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Unknown_SoundShader"};
	};

	class PersonalRadio_Vybor_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Vybor_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Vyshnoye_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Vyshnoye_Mercenaries_SoundShader"};
	};

	class PersonalRadio_Zelenogorsk_Mercenaries_SoundSet
	{
		soundShaders[] = {"PersonalRadio_Zelenogorsk_Mercenaries_SoundShader"};
	};
};