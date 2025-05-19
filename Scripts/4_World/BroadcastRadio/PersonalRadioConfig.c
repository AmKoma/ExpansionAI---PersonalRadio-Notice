class PersonalRadioConfig
{
    ref array<string> AllowedFactions;

    void Load()
    {
        string folder = "$profile:Albtrauminsel/";
        string path = folder + "Broadcast.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        if (!FileExist(path))
        {
            AllowedFactions = new array<string>();
            AllowedFactions.Insert("East");
            AllowedFactions.Insert("Mercenaries");
            JsonFileLoader<PersonalRadioConfig>.JsonSaveFile(path, this);
            return;
        }

        JsonFileLoader<PersonalRadioConfig>.JsonLoadFile(path, this);
    }

    void Save()
    {
        if (!AllowedFactions)
            AllowedFactions = new array<string>();

        JsonFileLoader<PersonalRadioConfig>.JsonSaveFile("$profile:Albtrauminsel/Broadcast.json", this);
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