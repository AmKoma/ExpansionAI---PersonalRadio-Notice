class PersonalRadioConfig
{
    ref array<string> AllowedFactions;
    float TimeToFirstBroadcast;
    float MinTimeForNextBroadcast;
    float MaxTimeForNextBroadcast;
    float MinBroadcastChance;
    float MaxBroadcastChance;

    void Load()
    {
        string folder = "$profile:Broadcast/";
        string path = folder + "Settings.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        if (!FileExist(path))
        {
            AllowedFactions = new array<string>();
            AllowedFactions.Insert("Mercenaries");

            TimeToFirstBroadcast = 60;
            MinTimeForNextBroadcast = 900;
            MaxTimeForNextBroadcast = 5400;
            MinBroadcastChance = 0.3;
            MaxBroadcastChance = 0.7;

            JsonFileLoader<PersonalRadioConfig>.JsonSaveFile(path, this);
            return;
        }

        JsonFileLoader<PersonalRadioConfig>.JsonLoadFile(path, this);
    }

    void Save()
    {
        if (!AllowedFactions)
            AllowedFactions = new array<string>();

        if (!TimeToFirstBroadcast)
        {
            TimeToFirstBroadcast = 60;
            MinTimeForNextBroadcast = 900;
            MaxTimeForNextBroadcast = 5400;
            MinBroadcastChance = 0.3;
            MaxBroadcastChance = 0.7;
        }

        JsonFileLoader<PersonalRadioConfig>.JsonSaveFile("$profile:Broadcast/Settings.json", this);
    }

    bool IsFactionAllowed(string name)
    {
        if (!AllowedFactions)
            return false;

        foreach (string f : AllowedFactions)
        {
            if (f == name)
                return true;
        }
        return false;
    }
}
