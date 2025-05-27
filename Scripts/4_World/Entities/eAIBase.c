modded class eAIBase
{
    ref Timer m_FunkBroadcastTimer;

    override void EEInit()
    {
        super.EEInit();

        if (GetGame().IsServer())
        {
            float delay = PersonalRadioConfigLoader.Get().TimeToFirstBroadcast;
            m_FunkBroadcastTimer = new Timer(CALL_CATEGORY_SYSTEM);
            m_FunkBroadcastTimer.Run(delay, this, "TriggerFunkBroadcast", null, false);
        }
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);

        if (m_FunkBroadcastTimer)
        {
            m_FunkBroadcastTimer.Stop();
            m_FunkBroadcastTimer = null;
        }
    }

    void TriggerFunkBroadcast()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        eAIGroup group = GetGroup();
        if (!group)
        {
            ScheduleNextFunk();
            return;
        }

        if(!IsAlive()){
            return;
        }

        eAIFaction factionObj = group.GetFaction();
        if (!factionObj)
        {
            ScheduleNextFunk();
            return;
        }

        string faction = factionObj.GetName();

        // Fraktion erlaubt?
        if (!PersonalRadioConfigLoader.Get().IsFactionAllowed(faction))
        {
            if (m_FunkBroadcastTimer)
            {
                m_FunkBroadcastTimer.Stop();
                m_FunkBroadcastTimer = null;
            }
            return;
        }

        // Dynamische Broadcast-Chance prüfen
        float minChance = PersonalRadioConfigLoader.Get().MinBroadcastChance;
        float maxChance = PersonalRadioConfigLoader.Get().MaxBroadcastChance;
        float actualChance = Math.RandomFloatInclusive(minChance, maxChance);

        if (Math.RandomFloat01() > actualChance)
        {
            ScheduleNextFunk();
            return;
        }

        vector pos = GetPosition();
        string location = GetLocationName(pos);
        if (location == "")
        {
            location = "Unknown";
        }

        location.Replace(" ", "_");
        string soundSet = string.Format("PersonalRadio_%1_%2_SoundSet", location, faction);

        if (!GetGame().ConfigIsExisting("CfgSoundSets " + soundSet))
        {
            soundSet = "PersonalRadio_Unknown_SoundSet";
        }

        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player)
                continue;

            float dist = vector.Distance(player.GetPosition(), pos);
            if (dist > PersonalRadioConfigLoader.Get().AISearchRadius)
                continue;

            PlayerIdentity identity = player.GetIdentity();
            if (!identity)
            {
                continue;
            }

            array<EntityAI> items = new array<EntityAI>();
            player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

            foreach (EntityAI item : items)
            {
                PersonalRadio radio = PersonalRadio.Cast(item);
                if (radio && radio.IsOperational())
                {
                    GetGame().RPCSingleParam(radio, PersonalRadio.RPC_RADIO_SOUND_PLAY, new Param1<string>(soundSet), true, player.GetIdentity());
                }
            }
        }

        ScheduleNextFunk();
    }

    void ScheduleNextFunk()
    {
        float delay = Math.RandomFloatInclusive(PersonalRadioConfigLoader.Get().MinTimeForNextBroadcast, PersonalRadioConfigLoader.Get().MaxTimeForNextBroadcast);
        if (!m_FunkBroadcastTimer)
            m_FunkBroadcastTimer = new Timer(CALL_CATEGORY_SYSTEM);

        m_FunkBroadcastTimer.Run(delay, this, "TriggerFunkBroadcast", null, false);
    }

    string GetLocationName(vector pos)
    {
        array<ref ExpansionLocation> locations = ExpansionLocation.GetWorldLocations();
        ExpansionLocation closest;
        float closestDistSq = int.MAX;
        vector pos2D = Vector(pos[0], 0, pos[2]);

        foreach (ExpansionLocation location : locations)
        {
            float distSq = vector.DistanceSq(pos2D, location.Position);
            if (distSq <= (location.Radius * location.Radius) && distSq < closestDistSq)
            {
                closest = location;
                closestDistSq = distSq;
            }
        }

        if (closest)
            return closest.Name;

        return "";
    }
}
