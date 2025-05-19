modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();

        Print("[MissionServer] Initialisiere PersonalRadio Config ...");
        PersonalRadioTickManager.Init();
    }
}
